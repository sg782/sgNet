#pragma once

#ifndef AFFINE_H
#define AFFINE_H

#include <vector>
#include <iostream>
namespace SgNet{

    template <typename T>

    class Affine{
        
    public:
        T w;
        T inputs;
        std::vector<double> b;

        Affine(int nDims, std::vector<int> dims);
        
        T forward(T inputs);

        T backward(T dValues);

    };
    
    template <typename T>
    Affine<T>::Affine(int nDims, std::vector<int> dims){
        b.resize(dims[0]);

        w = T(dims);
    }

    template <typename T>
    T Affine<T>::forward(T inputs){
        this-> inputs = inputs;

        // forward pass on generic tensor type
        T out = inputs * w;
        out = out + b;
        return out;
    }

    template <typename T>
    T Affine<T>::backward(T dValues){
        return dValues;
}





}

#endif