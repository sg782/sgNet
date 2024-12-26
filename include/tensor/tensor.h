#pragma once

#ifndef TENSOR_H
#define TENSOR_H

#include "tensor/vector.h"
#include "utils/frisbee.h"

namespace SgNet{

    class Tensor{
    private:
        void setIndexDims();

    public:
        int nDims;
        int flatLength;
        Vector dims;
        Vector indexDims;
        Vector data;

        Tensor() = default;
        Tensor(Vector dims);

        void setConstant(double val);
        void setRandomGaussian(double mean, double stdDev);

        Tensor matMult(Tensor b);


        void setData(Vector data);

        // most important function 
        Tensor operator[] (int index);
        const Tensor operator[] (int index) const;


        Tensor getAxis(int axis,int index);
        Vector asVector();




        Frisbee at(int index);

        Frisbee at(Vector indices);

        /*
        make Tensor at(index) and at(vector indices) functions to get frisbee output
        */

       Tensor operator+ (const double val) const;
       Tensor operator- (const double val) const;
       Tensor operator* (const double val) const;
       Tensor operator/ (const double val) const;

       void operator+=(const double val);
       void operator-=(const double val);
       void operator*=(const double val);
       void operator/=(const double val);


        void print();
    };
}



#endif