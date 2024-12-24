#include "tensor/tensor.h"
#include "tensor/vector.h"

SgNet::Tensor::Tensor(Vector dims){
    nDims = dims.size();
    this->dims = dims;
    flatLength = static_cast<int>(dims.product());
    data = Vector(flatLength);
}




SgNet::Tensor& SgNet::Tensor::operator[](int index){
    // the [] operator will return a Tensor with dim of nDims - 1. We are indexing the largest index, so it would be dims[0], thus our resulting dim is dims.slice(1,dims.size())

    SgNet::Vector newDims = dims.slice(1,dims.size());

    int startIdx = index * newDims.product();
    int endIdx = (index+1)*newDims.product();


    // maybe for efficiency, we make a setData, function which just sets the data of the new tensor to be pointing to the same memory as the data, instead of doing that manually in a loop
    

    SgNet::Tensor out(newDims);
}

const SgNet::Tensor SgNet::Tensor::operator[] (int index) const{
    
}