#include "neural/layer/Affine1d.h"
#include <vector>
#include <iostream>
#include "utils/timer.h"
#include <cmath>

// Standard Affine transformation, where each row of data is a different item

SgNet::Affine1d::Affine1d(int nDims, std::vector<int> dims,double learningRate){
    
    this->learningRate = learningRate;
    b.resize(dims[1]);
    b = Vector(dims[1]);
    b.setConstant(0.0);

    w = Tensor(dims);
    w.setRandomGaussian(0,1);
    w *= std::sqrt(2. / dims[0]);
}

SgNet::Tensor SgNet::Affine1d::forward(Tensor inputs){

    this-> inputs = inputs;
    // forward pass on generic tensor type
    Tensor out = inputs.matMult(w);

    out.printShape();
    std::cout << b.size() << "\n";


    out += b;

    return out;
}

SgNet::Tensor SgNet::Affine1d::backward(Tensor dValues){

    Tensor dW = inputs.transpose2d().matMult(dValues);
    Vector dB = dValues.axisSum(1);

    Tensor dInputs = dValues.matMult(w.transpose2d());

    // update weights
    w -= (dW * learningRate);
    b -= (dB * learningRate);

    return dInputs;
}



// SgNet::Affine1d::Affine1d(int nDims, std::vector<int> dims,double learningRate){
    
//     this->learningRate = learningRate;
//     b.resize(dims[1]);
//     b = Vector(dims[1]);
//     b.setConstant(0.0);

//     w = Tensor2d(dims);
//     w.setRandomGaussian(0,1);
//     w *= std::sqrt(2. / dims[0]);
// }

// SgNet::Tensor2d SgNet::Affine1d::forward(Tensor2d inputs){
//     this-> inputs = inputs;

//     // forward pass on generic tensor type

//     Tensor2d out = inputs.matMult(w);

//     out += b;



//     return out;
// }

// SgNet::Tensor2d SgNet::Affine1d::backward(Tensor2d dValues){

//     Tensor2d dW = inputs.transpose().matMult(dValues);
//     Vector dB = dValues.colSum();

//     Tensor2d dInputs = dValues.matMult(w.transpose());

//     // update weights
//     w -= (dW * learningRate);
//     b -= (dB * learningRate);

//     return dInputs;
// }