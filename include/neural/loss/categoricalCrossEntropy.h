#pragma once

#ifndef CAT_CROSS_ENTROPY_H
#define CAT_CROSS_ENTROPY_H

#include "tensor/tensor2d.h"

namespace SgNet{
    class CCE {
    public:

        CCE();

        double calculate(Tensor2d x, Vector y);

        Tensor2d backward(Tensor2d ypred, Vector y);
    };
}




#endif