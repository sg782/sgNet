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
#include "tensor/tensor.h"
#include "neural/layer/convolution2d.h"

int main() {
    using namespace SgNet;

    Tensor inputs(std::vector<int>{1,1,10,10});\
    inputs.setRandomInt(0,5);



    double learningRate = 0.01;
	
	int kernelWidth = 3;
	std::array<int, 2> kernelDims = { kernelWidth,kernelWidth };
	int inputChannels = 1;
	int numFilters = 1;
	int strideLength = 1;
	int padding = 0;

	int convOutDim = (10 - kernelWidth+2*padding)/strideLength + 1;

    


    Convolution2d conv = Convolution2d(kernelDims, inputChannels, numFilters, learningRate, strideLength, padding);


    Tensor out = conv.forward(inputs);

    std::cout << "\nOut complete\n";

    Tensor back = conv.backward(out);

    std::cout << "\nBack complete\n";





    





}