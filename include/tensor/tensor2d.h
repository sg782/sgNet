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

        void test();
        void print();
    };

}

#endif