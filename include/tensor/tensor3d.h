#pragma once

#ifndef TENSOR3d_H
#define TENSOR3d_H

#include "tensor/tensor2d.h"
#include "tensor/vector.h"


namespace SgNet{

    class Tensor3d{
    public:

        Tensor3d(int nDimensions,std::vector<int> Dimensions);

        void test();
        void print();
    };

}

#endif