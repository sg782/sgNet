#pragma once

#ifndef LEAKYRELU_H
#define LEAKYRELU_H

#include "tensor/tensor2d.h"

namespace SgNet{
    class LeakyRelu {
    public:
        int inputDim;
        double leakiness;
        Tensor2d inputs;

        LeakyRelu() = default;
        LeakyRelu(int nInput,double leakiness);

        Tensor2d forward(Tensor2d& input);

        Tensor2d backward(Tensor2d& dValues);

    };
}




#endif