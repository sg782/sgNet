#include "neural/layer/relu.h"
#include <vector>
#include "tensor/tensor.h"

SgNet::Relu::Relu(std::vector<int> dims){

}

SgNet::Tensor SgNet::Relu::forward(Tensor inputs){
    this->inputs = inputs;
    inputs.min(0);
    return inputs;
}

SgNet::Tensor SgNet::Relu::backward(Tensor dValues){
    return (inputs>0) * dValues;
}