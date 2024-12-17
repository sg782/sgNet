#pragma once

#ifndef TENSOR_H
#define TENSOR_H

#include <vector>


namespace SgNet{

    class Tensor{
    public:
        int flatLength;
        int nDimensions;
        std::vector<int> dimensions;
        std::vector<double> flatVector;
        Tensor(int nDimensions,std::vector<int> Dimensions);

        void test();
        void print();
    };

}

#endif