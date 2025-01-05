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
#include "neural/layer/flatten.h"


int main() {
    using namespace SgNet;


    int maxRows = 11;

    Tensor data(std::vector<int>{maxRows,1,28,28});
    Vector labels(maxRows);

    loadMnistConvData(data,labels,maxRows);

	data -= 127.5;
    data/=127.5;



    double learningRate = 0.05;

	
	int kernelWidth = 3;
	std::array<int, 2> kernelDims = { kernelWidth,kernelWidth };
	int inputChannels = 1;
	int numFilters = 1;
	int strideLength = 1;
	int padding = 0;

	int convOutDim = (28 - kernelWidth+2*padding)/strideLength + 1;
	labels.print();



	Convolution2d conv1 = Convolution2d(kernelDims, inputChannels, numFilters, learningRate, strideLength, padding);
    Relu r1 = Relu();
	Flatten f1 = Flatten(2);
    Affine1d a2 = Affine1d(2,std::vector<int>{676,10},learningRate);
    Softmax s2 = Softmax(0);
    CCE cce = CCE();

    int nIters = 10;

    for(int i=0;i<nIters;i++){
		std::cout << "begin loop\n";

				std::cout << "4445\n";

        Tensor out1 = conv1.forward(data);

		std::cout << "45\n";


        Tensor rOut1 = r1.forward(out1);

		Tensor flat1 = f1.forward(rOut1);

				std::cout << "345\n";




        Tensor out2 = a2.forward(flat1);


		std::cout << "455\n";

        Tensor sOut2 = s2.forward(out2,1);

				std::cout << "145\n";



        double loss = cce.calculate(sOut2,labels);


        std::cout << "Loss: " << loss << "\n";

        Tensor gradients = cce.backward(sOut2,labels);
        std::cout << "here\n";

        Tensor sBack2 = s2.backward(gradients);
                std::cout << "here\n";

        Tensor back2 = a2.backward(sBack2);
                std::cout << "here\n";

		Tensor flatBack1 = f1.backward(back2);

        Tensor rBack1 = r1.backward(flatBack1);
                std::cout << "here\n";

        Tensor back1 = conv1.backward(rBack1);
                std::cout << "here\n";

		std::cout << "end loop\n";

    }






}