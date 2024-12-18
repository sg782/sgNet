#pragma once

#ifndef TENSOR_2D_H
#define TENSOR_2D_H

#include <vector>
#include "tensor/vector.h"


namespace SgNet{

    class Tensor2d{
    public:
        std::vector<int> dimensions;
        std::vector<SgNet::Vector> data;
        Tensor2d() = default;
        Tensor2d(std::vector<int> Dimensions);


        // methods
        void print();
        void setConstant(double val);


        // row and col operations
        std::vector<Vector> byRow();
        std::vector<Vector> byCol();


        Tensor2d transpose();


        // operator overloads
        // each have a single value, vector, and matrix form
        // currently, vector operations is only rowwise, Idk yet how i will do the colwise and still be able to keep std::vectors
        // eventually, the vector and matrix overloads will need an overhaul to allow for broadcasting (not yet);

        // addition
        Tensor2d operator+ (const double val) const;
        Tensor2d operator+ (const std::vector<double> vals) const;
        Tensor2d operator+ (const Tensor2d& r) const;

        // subtraction
        Tensor2d operator- (const double val) const;
        Tensor2d operator- (const std::vector<double> vals) const;
        Tensor2d operator- (const Tensor2d& r) const;


        //multiplication
        Tensor2d operator* (const double val) const;
        Tensor2d operator* (const std::vector<double> vals) const;
        Tensor2d operator* (const Tensor2d& r) const;

        //division
        Tensor2d operator/ (const double val) const;
        Tensor2d operator/ (const std::vector<double> vals) const;
        Tensor2d operator/ (const Tensor2d& r) const;

        // index operator. It returns a vector which can also be indexed.
        SgNet::Vector& operator[] (int index);


        
    };

}

#endif