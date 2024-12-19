#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>

int main() {

   using namespace SgNet;

    Tensor2d g = Tensor2d({3,5});

    g.byCol()[0] = 8;

    g[2][2] = 9;

    g.print();

     
    return 0;
}