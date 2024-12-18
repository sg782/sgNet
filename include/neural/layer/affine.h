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
    





}

#endif