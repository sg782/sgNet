#include "neural/layer/leakyRelu.h"

SgNet::LeakyRelu::LeakyRelu(int inputSize,double leakiness) : inputDim(inputSize),leakiness(leakiness) {

}

SgNet::Tensor2d SgNet::LeakyRelu::forward(SgNet::Tensor2d& input) {
	inputs = input;

	SgNet::Tensor2d mask = (inputs > 0) + ((inputs<= 0) * leakiness);


	SgNet::Tensor2d output = input* mask;// *mask;


	return output;
}

SgNet::Tensor2d SgNet::LeakyRelu::backward(SgNet::Tensor2d& dValues) {
	SgNet::Tensor2d mask = (inputs> 0)+ ((inputs<= 0) * leakiness);

	SgNet::Tensor2d dInputs = dValues* mask;

	return dInputs;
}
