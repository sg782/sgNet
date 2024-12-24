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

        void setConstant(double val);


        void setData(Vector data);

        // most important function 
        Tensor operator[] (int index);
        const Tensor operator[] (int index) const;



        void print();
    };
}



#endif