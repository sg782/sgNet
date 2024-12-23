#include "neural/layer/relu.h"
#include <vector>

SgNet::Relu::Relu(std::vector<int> dims){

}

SgNet::Tensor2d SgNet::Relu::forward(Tensor2d inputs){
    this->inputs = inputs;
    inputs.min(0);
    return inputs;
}

SgNet::Tensor2d SgNet::Relu::backward(Tensor2d dValues){
    return (inputs>0) * dValues;
}