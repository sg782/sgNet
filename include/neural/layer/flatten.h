#pragma once

#ifndef FLATTEN_H
#define FLATTEN_H

#include "tensor/tensor.h"


namespace SgNet{

    class Flatten{

    public:
        int nOutputDims;
        Vector inputDims;
        Tensor out;

        Flatten() = default;
        Flatten(int outputDims);

        Tensor forward(Tensor inputs);

        Tensor backward(Tensor dValues);
    };


}

// flatten layer

/*
We need to know
1. desired output dim
    - flatten the last N layers into a vector (for each input), where N = (inDims-outDims+1)

*/




#endif