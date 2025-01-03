#include "neural/layer/leakyRelu.h"

SgNet::LeakyRelu::LeakyRelu(int inputSize,double leakiness) : inputDim(inputSize),leakiness(leakiness) {

}

SgNet::Tensor SgNet::LeakyRelu::forward(SgNet::Tensor& input) {
	inputs = input;

	SgNet::Tensor mask = (inputs > 0) + ((inputs<= 0) * leakiness);


	SgNet::Tensor output = input* mask;// *mask;


	return output;
}

SgNet::Tensor SgNet::LeakyRelu::backward(SgNet::Tensor& dValues) {
	SgNet::Tensor mask = (inputs> 0)+ ((inputs<= 0) * leakiness);

	SgNet::Tensor dInputs = dValues* mask;

	return dInputs;
}
