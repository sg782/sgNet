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


    Tensor2d dummyData({50,100});
    dummyData.setRandom(0,1);
    Affine testAffine(2,{100,100},learningRate);


    // we will use a benchmark of a dataset of 150 samples, each holding 100 double values, passing through a 100->100 affine
    /*

        BASE (no optimizations): 4810ms 
        
        1. Matrix multiplication was very slow, turns out i was a dummy and kept calling the Tensor2d.byCol() function for each row. 
           The change was to extract the byCol() call out of the matMult loop, which is pretty obvious in hindsight. Renders a massive
           speedup
           - NEW TIME: 10.8ms
             - 480x improvement. This is all the optimization we need for now
        
    
    */


    t.start();
    int numTests = 5;
    double cumulativeTime = 0.0;
    
    for(int i=0;i<numTests;i++){
        t.timeStop("Start forward");
        Tensor2d out = testAffine.forward(dummyData);
        cumulativeTime += t.timeStop("End forward");

        out.printShape();
    }

    double avgTime = cumulativeTime/numTests;

    std::cout << "Average Time: " << avgTime << " ms\n";




    // col major vs row major test
    // Tensor2d test({5000,5000});
    // test.setConstant(0);
    // t.start();
    // for(int i=0;i<test.numRows();i++){
    //     for(int j=0;j<test.numCols();j++){
    //         double val = test[i][j].val();
    //     }
    // }
    // t.timeStop("end indexing");






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