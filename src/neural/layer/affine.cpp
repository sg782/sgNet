#include "neural/layer/affine.h"
#include <vector>
#include <iostream>
#include "utils/timer.h"
#include <cmath>

// due to the existence of the Generic type, we must do somethign special here
// should i look into inheritance for the tensors (yes);


SgNet::Affine::Affine(int nDims, std::vector<int> dims,double learningRate){
    
    this->learningRate = learningRate;
    b.resize(dims[1]);
    b = Vector(dims[1]);
    b.setConstant(0.0);

    w = Tensor2d(dims);
    w.setRandomGaussian(0,1);
    w *= std::sqrt(2. / dims[0]);
}

SgNet::Tensor2d SgNet::Affine::forward(Tensor2d inputs){
    this-> inputs = inputs;

    // forward pass on generic tensor type
    SgNet::Timer t = SgNet::Timer();

    Tensor2d out = inputs.matMult(w);

    out.byRow() += b;



    return out;
}

SgNet::Tensor2d SgNet::Affine::backward(Tensor2d dValues){



    Tensor2d dW = inputs.transpose().matMult(dValues);
    Vector dB = dValues.colSum();



    Tensor2d dInputs = dValues.matMult(w.transpose());



    // update weights
    w -= (dW * learningRate);
    b -= (dB * learningRate);

    return dInputs;
}