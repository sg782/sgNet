#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>

int main() {

    using namespace SgNet;


    Affine<Tensor2d> layer = Affine<Tensor2d>(2,{3,4});



    Tensor2d a = Tensor2d({2,3});

    a.setConstant(1);
    a[1].set({-1,5,8});


    Tensor2d out = layer.forward(a);

    out.print();

     
    return 0;
}