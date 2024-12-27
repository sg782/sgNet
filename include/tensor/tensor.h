#pragma once

#ifndef TENSOR_H
#define TENSOR_H

#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <vector>
#include "initializer_list"

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

        Tensor(std::vector<double> dims);
        Tensor(std::vector<int> dims);
        Tensor(std::initializer_list<int>dims);



        void setConstant(double val);
        void setRandomGaussian(double mean, double stdDev);
        void setRandomInt(int low, int high);


        double sum() const;
        int getDim(int idx) const;


        Tensor matMult(Tensor b);

        Vector getDimensionalIndex(int index);


        void setData(Vector data);

        // most important function 
        Tensor operator[] (int index);
        const Tensor operator[] (int index) const;


        Tensor getAxis(int axis,int index);
        Vector asVector();
        Tensor block(Vector startPoint, Vector blockDims);
        void copyData(Tensor other);




        Frisbee at(int index);

        Frisbee at(Vector indices);
        Frisbee at(std::vector<int> indices);

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

       void operator-=(Tensor other);
       void operator*=(Tensor other);

       void operator= (Tensor b);


        void print();
    };
}



#endif