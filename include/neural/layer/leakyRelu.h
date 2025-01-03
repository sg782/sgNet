#pragma once

#ifndef LEAKYRELU_H
#define LEAKYRELU_H

#include "tensor/Tensor.h"

namespace SgNet{
    class LeakyRelu {
    public:
        int inputDim;
        double leakiness;
        Tensor inputs;

        LeakyRelu() = default;
        LeakyRelu(int nInput,double leakiness);

        Tensor forward(Tensor& input);

        Tensor backward(Tensor& dValues);

    };
}




#endif