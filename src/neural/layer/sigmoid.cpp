#include "neural/layer/sigmoid.h"

SgNet::Sigmoid::Sigmoid(int inputSize) : inputDim(inputSize) {

}

SgNet::Tensor2d SgNet::Sigmoid::forward(const SgNet::Tensor2d& input) {
	// sigmoid activation
	SgNet::Tensor2d output = calculateSigmoid(input);

	inputs = input;
	sigmoidInputs = output;
	
	return output;
}

SgNet::Tensor2d SgNet::Sigmoid::backward(SgNet::Tensor2d& dValues) {

	SgNet::Tensor2d derivative = sigmoidInputs * ((sigmoidInputs * -1) + 1);

	SgNet::Tensor2d output = derivative * dValues;


	return output;
}

// helper function, since it is used multiple times
SgNet::Tensor2d SgNet::Sigmoid::calculateSigmoid(SgNet::Tensor2d input) {
	// sigmoid activation
	SgNet::Tensor2d output = 1 / (((input*-1).exp()) + 1 );
	return output;
}
