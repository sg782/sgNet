#pragma once

#ifndef TENSOR_H
#define TENSOR_H

#include "tensor/tensor2d.h"
#include "tensor/vector.h"


namespace SgNet{

    class Tensor3d{
    public:
        Tensor3d(std::vector<int> Dimensions);

        void print();
    };

}

#endif