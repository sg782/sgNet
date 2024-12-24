#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include "utils/frisbee.h"

// I should definitely make this nestable
/*
It would simpify things in higher dimensions i think;
I will do it later if it proves useful

will require some recursion for operations.
The vectorwise operations may still remain pretty simple, as calling an ddition of two vectors V[i] + Q[i]
would just do the addition of whatever each index returns, if it is another vector then it will continue the addition.
i think

<><><><><><>
On the contrary to the previous remark, I will have the data be pointers

*/

namespace SgNet {
    

    class Vector{
    public:
        std::vector<Frisbee> data;
        Vector() = default;
        Vector(int size);

    

        void print();
        void resize(int newSize);


        int size() const;

        double sum() const;
        double product() const;
  

        double dot(const Vector& v);

        void setConstant(double val);
        void setRandomGaussian(double mean, double stdDev);
        void set(std::vector<double> vals);
        void set(SgNet::Vector vals);
        void setReference(SgNet::Vector vals);


        void max(double val);
        double max();

        void min(double val);
        double min();

        Vector exp() const;
        Vector square() const;
        Vector tanh() const;

        Vector slice(int startIndex, int endIndex) const;

        
        Vector operator+ (const double val) const;
        Vector operator+ (const Vector vals) const;
        void operator+= (const double val);
        void operator+= (const Vector vals);

        Vector operator- (const double val) const;
        Vector operator- (const Vector vals) const;
        void operator-= (const double val);
        void operator-= (const Vector vals);

        Vector operator* (const double val) const;
        Vector operator* (const Vector vals) const;
        void operator*= (const double val);
        void operator*= (const Vector vals);

        Vector operator/ (const double val) const;
        Vector operator/ (const Vector vals) const;
        void operator/= (const double val);
        void operator/= (const Vector vals);


        friend Vector operator+ (double scalar, Vector vec){
            Vector out(vec.size());
            for(int i=0;i<vec.size();i++){
                out[i] = scalar + vec[i].val();
            }
            return out;
        }
        friend Vector operator- (double scalar, Vector vec){
            Vector out(vec.size());
            for(int i=0;i<vec.size();i++){
                out[i] = scalar - vec[i].val();
            }
            return out;
        }
        friend Vector operator* (double scalar, Vector vec){
            Vector out(vec.size());
            for(int i=0;i<vec.size();i++){
                out[i] = scalar * vec[i].val();
            }
            return out;
        }
        friend Vector operator/ (double scalar, Vector vec){
            Vector out(vec.size());
            for(int i=0;i<vec.size();i++){
                out[i] = scalar / vec[i].val();
            }
            return out;
        }


        Vector operator> (const double val) const;
        Vector operator> (const Vector vals) const;
        Vector operator>= (const double val) const;
        Vector operator>= (const Vector vals) const;

        Vector operator< (const double val) const;
        Vector operator< (const Vector vals) const;
        Vector operator<= (const double val) const;
        Vector operator<= (const Vector vals) const;



        // equality overloads make a copy, NOT a reference
        // maybe I should change that
        // it would make sense for SET to do the copying and = to make a reference
        void operator= (double val);
        void operator= (const std::vector<double> v);
        void operator= (const Vector v);

        Frisbee& operator[] (int index);
        const Frisbee& operator[] (int index) const;
    };

}

#endif