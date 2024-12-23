#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>
#include "neural/layer/softmax.h"
#include "neural/loss/categoricalCrossEntropy.h"
#include "utils/fileReading.h"
#include "neural/layer/relu.h"

int main() {
    using namespace SgNet;

    int numSamples = 100;
    double learningRate = 0.005;

    Tensor2d data({numSamples,784});
    Vector labels({numSamples});

    loadData(data,labels,numSamples);
    data -= 127.5;
    data /= 127.5;


    Affine a1 = Affine(2,{784,128},learningRate);
    Relu r1 = Relu({128});

    Affine a2 = Affine(2,{128,10},learningRate);
    Softmax s2 = Softmax(10);

    CCE cce = CCE();


    int nIters = 1;

    for(int i=0;i<nIters;i++){
        std::cout << "\nhere\n";
        Tensor2d out1 = a1.forward(data);
                std::cout << "\nhere\n";

        Tensor2d rOut1 = r1.forward(out1);
                std::cout << "\nhere\n";


        // Tensor2d out2 = a2.forward(rOut1);
        // out2.printShape();
        // Tensor2d sOut2 = s2.forward(out2);

        // sOut2.printShape();

    }

     
    return 0;
}