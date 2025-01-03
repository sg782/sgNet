#include "tensor/tensor2d.h"
#include "neural/layer/affine1d.h"
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
#include "tensor/tensor.h"
#include "neural/layer/convolution2d.h"
#include "neural/layer/affine_t.h"
#include "neural/layer/relu.h"
#include "neural/layer/softmax.h"

int main() {
    using namespace SgNet;

    int maxRows = 10;

    Tensor data(std::vector<int>{10,784});
    Vector labels(maxRows);

    loadMnistData(data,labels,maxRows);

	data -= 127.5;
    data/=127.5;

    double learningRate = 0.005;


    Affine1d a1 = Affine1d(2,std::vector<int>{784,128},learningRate);
    Sigmoid r1 = Sigmoid(10);
    Affine1d a2 = Affine1d(2,std::vector<int>{128,10},learningRate);
    Softmax s2 = Softmax(0);
    CCE cce = CCE();

    int nIters = 10;

    for(int i=0;i<nIters;i++){
        Tensor out1 = a1.forward(data);


        Tensor rOut1 = r1.forward(out1);

        Tensor out2 = a2.forward(rOut1);

        Tensor sOut2 = s2.forward(out2,1);


        double loss = cce.calculate(sOut2,labels);

        std::cout << "Loss: " << loss << "\n";

        Tensor gradients = cce.backward(sOut2,labels);
        std::cout << "here\n";

        Tensor sBack2 = s2.backward(gradients);
                std::cout << "here\n";

        Tensor back2 = a2.backward(sBack2);
                std::cout << "here\n";

        Tensor rBack1 = r1.backward(back2);
                std::cout << "here\n";

        Tensor back1 = a1.backward(rBack1);
                std::cout << "here\n";

    }






}