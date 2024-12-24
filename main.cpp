#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>
#include "neural/layer/softmax.h"
#include "neural/loss/categoricalCrossEntropy.h"
#include "utils/fileReading.h"
#include "neural/layer/relu.h"
#include "utils/timer.h"
#include "neural/layer/sigmoid.h"
#include "neural/layer/tanh.h"
#include "neural/layer/leakyRelu.h"

int main() {
    using namespace SgNet;

    int numSamples = 100;
    double learningRate = 0.0005;


    Tensor2d data({numSamples,784});
    Vector labels(numSamples);

    loadData(data,labels,numSamples);
    data -=127.5;
    data/=127.5;

    // we will use a benchmark of a dataset of 150 samples, each holding 100 double values, passing through a 100->100 affine
    /*

        BASE (no optimizations): 4810ms 
        
        1. Matrix multiplication was very slow, turns out i was a dummy and kept calling the Tensor2d.byCol() function for each row. 
           The change was to extract the byCol() call out of the matMult loop, which is pretty obvious in hindsight. Renders a massive
           speedup
           - NEW TIME: 10.8ms
             - 480x improvement. This is all the optimization we need for now
        
    
    */

    Affine a1(2,{784,128},learningRate);
    LeakyRelu r1(128,.1);
    Affine a2(2,{128,10},learningRate);
    Softmax s2(128);

    CCE cce =CCE();

    // training loop
    int numIters = 30;

    for(int i=0;i<numIters;i++){

        // FORWARD
        Tensor2d out1 = a1.forward(data);
        Tensor2d rOut1 = r1.forward(out1);
        Tensor2d out2 = a2.forward(rOut1);
        Tensor2d sOut2 = s2.forward(out2);

        double loss = cce.calculate(sOut2,labels);
        std::cout << "Training loss: " << loss << "\n";

        Tensor2d gradient = cce.backward(sOut2,labels);

        // BACKWARD
        Tensor2d sBack2 = s2.backward(gradient);
        Tensor2d back2 = a2.backward(sBack2);
        Tensor2d rBack1 = r1.backward(back2);
        Tensor2d back1 = a1.backward(rBack1);
    }





    // 784 -> 128 affine layer 
    /*

    BEFORE:
    5 samples
      time: ~6000ms
       - this is truly terrible

    20 samples
      time: ~24000ms
       - at least it scales linearly haha

    AFTER:
    5 samples
      time: ~30 ms

    20 samples
      time: ~65ms

    much better
    */

     
    return 0;
}