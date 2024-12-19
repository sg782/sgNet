#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>

int main() {

    using namespace SgNet;

    Tensor2d a = Tensor2d({2,3});

    a.setRandom(0,1);
    a.print();

     
    return 0;
}