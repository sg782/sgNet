#pragma once

#ifndef SIGMOID_H
#define SIGMOID_H


#include "tensor/tensor2d.h"

namespace SgNet{

    class Sigmoid {
    public:
        int inputDim;

        Tensor2d inputs;
        Tensor2d sigmoidInputs;

        Sigmoid() = default;
        Sigmoid(int nInput);


        Tensor2d forward(const Tensor2d& input);

        Tensor2d backward(Tensor2d& dValues);

        Tensor2d calculateSigmoid(Tensor2d input);


    };


}


#endif