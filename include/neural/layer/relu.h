#pragma once

#ifndef RELU_H
#define RELU_H

#include <vector>
#include <iostream>
#include "tensor/vector.h"
#include "tensor/tensor2d.h"
namespace SgNet{


    class Relu{
        
    public:
        Tensor2d inputs;

        Relu(int nDims, std::vector<int> dims);
        
        Tensor2d forward(Tensor2d inputs);

        Tensor2d backward(Tensor2d dValues);

    };

}

#endif