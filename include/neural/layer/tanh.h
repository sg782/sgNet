#pragma once

#ifndef TANH_H
#define TANH_H

#include "tensor/tensor2d.h"


namespace SgNet{
    class Tanh{
    public:
        int inputDim;

        Tensor2d inputs;

        Tensor2d tanhInputs;

        Tanh() = default;
        Tanh(int nInput);


        SgNet::Tensor2d forward(SgNet::Tensor2d& input);

        SgNet::Tensor2d backward(const SgNet::Tensor2d& dValues);

        SgNet::Tensor2d calculateTanh(SgNet::Tensor2d input);

    };
}




#endif