#pragma once

#ifndef TENSOR_2D_H
#define TENSOR_2D_H

#include <vector>
#include "tensor/vector.h"
#include <array>


namespace SgNet{

    class Tensor2d{
    public:
        std::vector<int> dimensions;
        std::vector<SgNet::Vector> data;
        Tensor2d() = default;
        Tensor2d(std::vector<int> Dimensions);

        int numRows() const;
        int numCols() const;

        // methods
        void print();
        void setConstant(double val);
        void setRandomGaussian(double mean, double stdDev);
        std::vector<int> shape()const;

        void printShape()const;

        double sum() const;
        Vector rowSum();
        Vector colSum();

        Tensor2d matMult(SgNet::Tensor2d B);


        // row and col operations
        Tensor2d byRow();
        Tensor2d byCol();

        void max(double val);
        double max();

        void min(double val);
        double min();


        Tensor2d transpose();

        Tensor2d exp() const;
        Tensor2d square() const;
        Tensor2d tanh() const;

        // operator overloads
        // each have a single value, vector, and matrix form
        // currently, vector operations is only rowwise, Idk yet how i will do the colwise and still be able to keep std::vectors
        // eventually, the vector and matrix overloads will need an overhaul to allow for broadcasting (not yet);

        // addition
        Tensor2d operator+ (const double val) const;
        Tensor2d operator+ (const Vector& vals) const;
        Tensor2d operator+ (const Tensor2d& r) const;
        void operator+= (const double val);
        void operator+= (const Vector& vals);
        void operator+= (const Tensor2d& r);

        // subtraction
        Tensor2d operator- (const double val) const;
        Tensor2d operator- (const Vector& vals) const;
        Tensor2d operator- (const Tensor2d& r) const;
        void operator-= (const double val);
        void operator-= (const Vector& vals);
        void operator-= (const Tensor2d& r);

        //multiplication
        Tensor2d operator* (const double val) const;
        Tensor2d operator* (const Vector& vals) const;
        Tensor2d operator* (const Tensor2d& r) const;
        void operator*= (const double val);
        void operator*= (const Vector& vals);
        void operator*= (const Tensor2d& r);

        //division
        Tensor2d operator/ (const double val) const;
        Tensor2d operator/ (const Vector& vals) const;
        Tensor2d operator/ (const Tensor2d& r) const;
        void operator/= (const double val);
        void operator/= (const Vector& vals);
        void operator/= (const Tensor2d& r);


        friend Tensor2d operator+ (double scalar, Tensor2d tensor){
            Tensor2d out(tensor.shape());
            for(int i=0;i<tensor.numRows();i++){
                out[i] = scalar + tensor[i];
            }
            return out;
        }
        friend Tensor2d operator- (double scalar, Tensor2d tensor){
            Tensor2d out(tensor.shape());
            for(int i=0;i<tensor.numRows();i++){
                out[i] = scalar - tensor[i];
            }
            return out;
        }
        friend Tensor2d operator* (double scalar, Tensor2d tensor){
            Tensor2d out(tensor.shape());
            for(int i=0;i<tensor.numRows();i++){
                out[i] = scalar * tensor[i];
            }
            return out;
        }
        friend Tensor2d operator/ (double scalar, Tensor2d tensor){
            Tensor2d out(tensor.shape());
            for(int i=0;i<tensor.numRows();i++){
                out[i] = scalar / tensor[i];
            }
            return out;
        }

        Tensor2d operator> (const double val) const;
        Tensor2d operator> (const Vector vals) const;
        Tensor2d operator> (const Tensor2d vals)const;
        Tensor2d operator>= (const double val) const;
        Tensor2d operator>= (const Vector vals)const;
        Tensor2d operator>= (const Tensor2d vals)const;

        Tensor2d operator< (const double val) const;
        Tensor2d operator< (const Vector vals) const;
        Tensor2d operator< (const Tensor2d vals)const;
        Tensor2d operator<= (const double val)const;
        Tensor2d operator<= (const Vector vals)const;
        Tensor2d operator<= (const Tensor2d vals)const;

        // index operator. It returns a vector which can also be indexed.
        SgNet::Vector& operator[] (int index);
        const SgNet::Vector operator[] (int index) const;


        
    };

}

#endif