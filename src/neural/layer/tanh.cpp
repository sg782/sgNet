

#include "tensor/tensor2d.h"
#include "neural/layer/tanh.h"


SgNet::Tanh::Tanh(int inputSize) : inputDim(inputSize) {

}

SgNet::Tensor2d SgNet::Tanh::forward(SgNet::Tensor2d& input) {
	// Tanh activation
	SgNet::Tensor2d output = calculateTanh(input);
	tanhInputs = output;

	return output;
}

SgNet::Tensor2d SgNet::Tanh::backward(const SgNet::Tensor2d& dValues) {

	SgNet::Tensor2d derivative = 1 - tanhInputs.square();
	SgNet::Tensor2d output = derivative * dValues;

	return output;
}


// helper function, since it is used multiple times
SgNet::Tensor2d SgNet::Tanh::calculateTanh(SgNet::Tensor2d input) {
	// Tanh activation
	//SgNet::Tensor2d output = (input.array().exp() - (-1 * input.array()).exp()) / (input.array().exp() + (-1 * input.array()).exp());

    // need to calclulate our own tanh functions
	SgNet::Tensor2d output = input.tanh();
	return output;
}
