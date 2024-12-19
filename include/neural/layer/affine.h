#pragma once

#ifndef AFFINE_H
#define AFFINE_H

#include <vector>
#include <iostream>
#include "tensor/vector.h"
#include "tensor/tensor2d.h"
namespace SgNet{


    class Affine{
        
    public:
        double learningRate;
        Tensor2d w;
        Tensor2d inputs;
        Vector b;

        Affine(int nDims, std::vector<int> dims,double learningRate);
        
        Tensor2d forward(Tensor2d inputs);

        Tensor2d backward(Tensor2d dValues);

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