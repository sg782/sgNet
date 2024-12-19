#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>

int main() {

   using namespace SgNet;

    Tensor2d g = Tensor2d({3,5});

    Tensor2d h = g.byCol();

    h[1][0] = 4;
    g[2][2] = 9;

    g.print();

    h.print();
     
    return 0;
}