#pragma once

#ifndef AFFINE_TENSOR_H
#define AFFINE_TENSOR_H

#include <vector>
#include <iostream>
#include "tensor/vector.h"
#include "tensor/tensor2d.h"
#include "tensor/tensor.h"

namespace SgNet{


    class Affine_t{
        
    public:
        double learningRate;
        
        Tensor w;
        Tensor inputs;
        Tensor b;

        Affine_t(int nDims, std::vector<int> dims,double learningRate);
        
        Tensor forward(Tensor inputs);

        Tensor backward(Tensor dValues);

    };
    
    // template <typename T>
    // Affine<T>::Affine(int nDims, std::vector<int> dims){
        
    //     b = 0;

    //     w = T(dims);
    //     w.setRandom(0,1);
    // }

    // template <typename T>
    // T Affine<T>::forward(T inputs){
    //     this-> inputs = inputs;

    //     // forward pass on generic tensor type
    //     T out = inputs.matMult(w);
    //     out += b;
    //     return out;
    // }

    // template <typename T>
    // T Affine<T>::backward(T dValues){

        
    //     return dValues;
    //}
}

#endif