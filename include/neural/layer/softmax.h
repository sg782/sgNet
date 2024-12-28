#pragma once

#ifndef SOFTMAX_H
#define SOFTMAX_H

#include <vector>
#include <iostream>
#include "tensor/vector.h"
#include "tensor/Tensor.h"
namespace SgNet{


    class Softmax
    {
        
    public:
        Tensor inputs;
        Tensor output;

        Softmax(int nInputs);
        
        Tensor forward(Tensor inputs, int axis);

        Tensor backward(Tensor dValues);

    };

}

#endif