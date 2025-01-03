#include "neural/layer/sigmoid.h"

SgNet::Sigmoid::Sigmoid(int inputSize) : inputDim(inputSize) {

}

SgNet::Tensor SgNet::Sigmoid::forward(const SgNet::Tensor& input) {
	// sigmoid activation
	SgNet::Tensor output = calculateSigmoid(input);

	inputs = input;
	sigmoidInputs = output;
	
	return output;
}

SgNet::Tensor SgNet::Sigmoid::backward(SgNet::Tensor& dValues) {

	SgNet::Tensor derivative = sigmoidInputs * ((sigmoidInputs * -1) + 1);

	SgNet::Tensor output = derivative * dValues;


	return output;
}

// helper function, since it is used multiple times
SgNet::Tensor SgNet::Sigmoid::calculateSigmoid(SgNet::Tensor input) {
	// sigmoid activation
	SgNet::Tensor output = 1 / (((input*-1).exp()) + 1 );
	return output;
}
