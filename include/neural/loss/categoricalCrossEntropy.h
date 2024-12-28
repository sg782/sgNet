#pragma once

#ifndef CAT_CROSS_ENTROPY_H
#define CAT_CROSS_ENTROPY_H

#include "tensor/tensor2d.h"
#include "tensor/tensor.h"

namespace SgNet{
    class CCE {
    public:

        CCE();

        double calculate(Tensor x, Vector y);

        Tensor backward(Tensor ypred, Vector y);
    };
}




#endif