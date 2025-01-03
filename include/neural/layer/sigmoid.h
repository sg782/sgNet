#pragma once

#ifndef SIGMOID_H
#define SIGMOID_H


#include "tensor/Tensor.h"

namespace SgNet{

    class Sigmoid {
    public:
        int inputDim;

        Tensor inputs;
        Tensor sigmoidInputs;

        Sigmoid() = default;
        Sigmoid(int nInput);


        Tensor forward(const Tensor& input);

        Tensor backward(Tensor& dValues);

        Tensor calculateSigmoid(Tensor input);


    };


}


#endif