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

int main() {
    using namespace SgNet;


    Timer t = Timer();
    int numSamples = 20;
    double learningRate = 0.005;

    Tensor2d data({numSamples,784});
    Vector labels({numSamples});

    loadData(data,labels,numSamples);
    data -= 127.5;
    data /= 127.5;


    Affine a1 = Affine(2,{784,128},learningRate);

    t.start();
    t.timeStop("start affine");
    Tensor2d out1 = a1.forward(data);
    t.timeStop("End of affine layer");



    // 784 -> 128 affine layer 
    /*
    5 samples
      time: ~6000ms
       - this is truly terrible

    20 samples
      time: ~24000ms
       - at least it scales linearly haha
    */

     
    return 0;
}