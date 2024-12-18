#pragma once

#ifndef AFFINE_H
#define AFFINE_H

#include <vector>
namespace SgNet{

    template <typename T>

    class Affine{
        
    public:
        T w;
        std::vector<double> b;

        Affine(int nDims, std::vector<int> dims);
        
        T forward(T inputs);

        T backward(T dValues);

    };
    
    template <typename T>
    Affine<T>::Affine(int nDims, std::vector<int> dims){
        b.resize(dims[0]);
        w = T({5,6});
    }

    template <typename T>
    T Affine<T>::forward(T inputs){
        return inputs * 2;
    }

    template <typename T>
    T Affine<T>::backward(T dValues){
        return dValues;
}





}

#endif