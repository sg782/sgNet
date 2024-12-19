#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>

int main() {

    using namespace SgNet;

    double learningRate = 0.5;
    Affine layer = Affine(2,{3,2},learningRate);

    Tensor2d g = Tensor2d({2,3});

    g.setConstant(3);

    Tensor2d out = layer.forward(g);

    Tensor2d out2 = layer.backward(g);
   
    out2.print();

     
    return 0;
}