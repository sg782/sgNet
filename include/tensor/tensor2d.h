#pragma once

#ifndef TENSOR_2D_H
#define TENSOR_2D_H

#include <vector>


namespace SgNet{

    class Tensor2d{
    public:
        std::vector<int> dimensions;
        std::vector<std::vector<double>> data;
        Tensor2d(std::vector<int> Dimensions);


        // methods
        void print();
        void setConstant(int val);


        // operator overloads
        Tensor2d operator+ (const Tensor2d& r) const;
        std::vector<double>& operator[] (int index);

        
    };

}

#endif