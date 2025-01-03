#pragma once

#ifndef TANH_H
#define TANH_H

#include "tensor/tensor.h"


namespace SgNet{
    class Tanh{
    public:
        int inputDim;

        Tensor inputs;

        Tensor tanhInputs;

        Tanh() = default;
        Tanh(int nInput);


        SgNet::Tensor forward(SgNet::Tensor& input);

        SgNet::Tensor backward(const SgNet::Tensor& dValues);

        SgNet::Tensor calculateTanh(SgNet::Tensor input);

    };
}




#endif