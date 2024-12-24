#pragma once

#ifndef TENSOR_H
#define TENSOR_H

#include "tensor/vector.h"




namespace SgNet{

    class Tensor{

    public:
        int nDims;
        int flatLength;
        Vector dims;
        Vector data;

        Tensor() = default;
        Tensor(Vector dims);

        // most important function 
        SgNet::Tensor& operator[] (int index);
        const SgNet::Tensor operator[] (int index) const;
    };
}



#endif