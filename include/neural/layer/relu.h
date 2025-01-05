#pragma once

#ifndef RELU_H
#define RELU_H

#include <vector>
#include <iostream>
#include "tensor/vector.h"
#include "tensor/Tensor.h"
namespace SgNet{


    class Relu{
        
    public:
        Tensor inputs;

        Relu();
        
        Tensor forward(Tensor inputs);

        Tensor backward(Tensor dValues);

    };

}

#endif