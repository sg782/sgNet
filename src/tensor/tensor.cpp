#include "tensor/tensor.h"
#include "tensor/vector.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "utils/frisbee.h"

SgNet::Tensor::Tensor(Vector dims){
    nDims = dims.size();
    this->dims.resize(nDims);
    this->dims = dims;

    this->setIndexDims();

    flatLength = static_cast<int>(dims.product());
    data.resize(flatLength);
    data = Vector(flatLength);
}

void SgNet::Tensor::setIndexDims(){
    indexDims.resize(nDims);
    indexDims.setConstant(1);
    for(int i=dims.size()-2;i>=0;i--){
        indexDims[i] = indexDims[i+1].val() * dims[i+1].val();
    }
}


void SgNet::Tensor::setConstant(double val){
    data.setConstant(val);
}

void SgNet::Tensor::setRandomGaussian(double mean, double stdDev){
    data.setRandomGaussian(mean,stdDev);
}



SgNet::Frisbee SgNet::Tensor::at(int index){
    if(nDims != 1){
        std::stringstream ss;
        ss << "Tensor has " << nDims << " dimensions. Use the Vector-based overload. Integer overload is only for one dimensional vectors.";
        throw std::invalid_argument(ss.str());
    }

    return data[index];
}

SgNet::Frisbee SgNet::Tensor::at(SgNet::Vector indices){
    // add dimensions checks

    if(nDims != indices.size()){
        std::stringstream ss;
        ss << "index vector is not of length " << nDims << "\n";
        throw std::invalid_argument(ss.str());
    }

    double dbIdx = indexDims.dot(indices);
    int index = static_cast<int>(dbIdx);
    
    return data[index];
}




void SgNet::Tensor::setData(Vector newData){
    if(newData.size()!=flatLength){
        // error
    }

    data.setReference(newData);
}


void SgNet::Tensor::print(){
    std::vector<int> printDims = std::vector<int>(nDims);
    
    printDims[nDims - 1] = dims[nDims -1].val();
    for(int i=nDims-2;i>=0;i--){
        printDims[i] = printDims[i+1] * dims[i].val();
    }
    for(int i=0;i<flatLength;i++){
        for(int j=0;j<printDims.size();j++){
            if(i % printDims[j] == 0){
                std::cout << "\n";
            }
        }
        std::cout << data[i].val() << " ";
    }
}




SgNet::Tensor SgNet::Tensor::operator[](int index){
    if(nDims<1){
        throw std::invalid_argument("you indexed too far !!!");
    }
    if(nDims==1){
        // maybe make a custom handling for 0 dimension tensors so they have just one value
    }
    // the [] operator will return a Tensor with dim of nDims - 1. We are indexing the largest index, so it would be dims[0], thus our resulting dim is dims.slice(1,dims.size())

    // how to handle the case where the tensor has 1 dimension, and indexing it (should) just return a value?
    // all i can think of is 


    SgNet::Vector newDims = dims.slice(1,dims.size());

    int startIdx = index * newDims.product();
    int endIdx = (index+1)*newDims.product();

    // maybe for efficiency, we make a setData, function which just sets the data of the new tensor to be pointing to the same memory as the data, instead of doing that manually in a loop
    

    SgNet::Tensor out(newDims);

    // this is where our issue is
    out.setData(data.slice(startIdx,endIdx));

    return out;
}

const SgNet::Tensor SgNet::Tensor::operator[] (int index) const{
    
    SgNet::Vector newDims = dims.slice(1,dims.size());

    int startIdx = index * newDims.product();
    int endIdx = (index+1)*newDims.product();


    // maybe for efficiency, we make a setData, function which just sets the data of the new tensor to be pointing to the same memory as the data, instead of doing that manually in a loop
    

    SgNet::Tensor out(newDims);
    out.setData(data.slice(startIdx,endIdx));

    return out;
}