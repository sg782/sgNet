#pragma once

#ifndef SOFTMAX_H
#define SOFTMAX_H

#include <vector>
#include <iostream>
#include "tensor/vector.h"
#include "tensor/tensor2d.h"
namespace SgNet{


    class Softmax
    {
        
    public:
        Tensor2d inputs;
        Tensor2d output;

        Softmax(int nInputs);
        
        Tensor2d forward(Tensor2d inputs);

        Tensor2d backward(Tensor2d dValues);

    };

}

#endif