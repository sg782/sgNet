

#include "tensor/Tensor.h"
#include "neural/layer/tanh.h"


SgNet::Tanh::Tanh(int inputSize) : inputDim(inputSize) {

}

SgNet::Tensor SgNet::Tanh::forward(SgNet::Tensor& input) {
	// Tanh activation
	SgNet::Tensor output = calculateTanh(input);
	tanhInputs = output;

	return output;
}

SgNet::Tensor SgNet::Tanh::backward(const SgNet::Tensor& dValues) {

	SgNet::Tensor derivative = 1 - tanhInputs.square();
	SgNet::Tensor output = derivative * dValues;

	return output;
}


// helper function, since it is used multiple times
SgNet::Tensor SgNet::Tanh::calculateTanh(SgNet::Tensor input) {
	// Tanh activation
	//SgNet::Tensor output = (input.array().exp() - (-1 * input.array()).exp()) / (input.array().exp() + (-1 * input.array()).exp());

    // need to calclulate our own tanh functions
	SgNet::Tensor output = input.tanh();
	return output;
}
