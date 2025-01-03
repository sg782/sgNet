#pragma once

#ifndef TENSOR_H
#define TENSOR_H

#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <vector>
#include "initializer_list"
#include "tensor2d.h"

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

        Vector axisSum(int axis);


        void setData(Vector data);

        Tensor transpose2d();


        // most important function 
        Tensor operator[] (int index);
        const Tensor operator[] (int index) const;


        Tensor getAxis(int axis,int index);
        Vector asVector();
        Tensor block(Vector startPoint, Vector blockDims);
        void copyData(Tensor other);
        void copyData(Tensor2d other);





        Frisbee at(int index);
        Frisbee at(Vector indices);
        Frisbee at(std::vector<int> indices);
        Tensor tensorAt(Vector indices);

        /*
        make Tensor at(index) and at(vector indices) functions to get frisbee output
        */

        void min(double val);

        Vector shape();

        Tensor square() const;
        Tensor tanh() const;
        Tensor exp() const;

        Tensor operator+ (const double val) const;
        Tensor operator- (const double val) const;
        Tensor operator* (const double val) const;
        Tensor operator/ (const double val) const;

        friend Tensor operator+ (double scalar, Tensor tensor){
            Tensor out(tensor.shape());
            out.data = scalar + tensor.data;
            return out;
        }

        friend Tensor operator- (double scalar, Tensor tensor){
            Tensor out(tensor.shape());
            out.data = scalar - tensor.data;
            return out;
        }
        friend Tensor operator* (double scalar, Tensor tensor){
            Tensor out(tensor.shape());
            out.data = scalar * tensor.data;
            return out;
        }
        friend Tensor operator/ (double scalar, Tensor tensor){
            Tensor out(tensor.shape());
            out.data = scalar / tensor.data;
            return out;
        }


        Tensor operator* (Tensor b);
        Tensor operator+ (Tensor b);

        void operator+=(const double val);
        void operator-=(const double val);
        void operator*=(const double val);
        void operator/=(const double val);

        void operator +=(Vector other);

        
        void operator-=(Tensor other);
        void operator*=(Tensor other);

        void operator= (Tensor b);

        Tensor operator> (double val);

        Tensor operator<= (double val);


        void print();
        void printShape();
    };
}



#endif