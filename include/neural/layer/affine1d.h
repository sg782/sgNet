#pragma once

#ifndef AFFINE_1D_H
#define AFFINE_1D_H

#include <vector>
#include <iostream>
#include "tensor/vector.h"
#include "tensor/tensor2d.h"
#include "tensor/tensor.h"
namespace SgNet{


    class Affine1d{
        
    public:
        double learningRate;
        Tensor w;
        Tensor inputs;
        Vector b;

        Affine1d(int nDims, std::vector<int> dims,double learningRate);
        
        Tensor forward(Tensor inputs);

        Tensor backward(Tensor dValues);

    };
    
    // template <typename T>
    // Affine1d<T>::Affine1d(int nDims, std::vector<int> dims){
        
    //     b = 0;

    //     w = T(dims);
    //     w.setRandom(0,1);
    // }

    // template <typename T>
    // T Affine1d<T>::forward(T inputs){
    //     this-> inputs = inputs;

    //     // forward pass on generic tensor type
    //     T out = inputs.matMult(w);
    //     out += b;
    //     return out;
    // }

    // template <typename T>
    // T Affine1d<T>::backward(T dValues){

        
    //     return dValues;
    //}
}

#endif