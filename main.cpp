#include "tensor/tensor2d.h"
#include "neural/layer/affine1d.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>
#include "neural/layer/softmax.h"
#include "neural/loss/categoricalCrossEntropy.h"
#include "utils/fileReading.h"
#include "neural/layer/relu.h"
#include "utils/timer.h"
#include "neural/layer/sigmoid.h"
#include "neural/layer/tanh.h"
#include "neural/layer/leakyRelu.h"
#include "tensor/tensor.h"
#include "neural/layer/convolution2d.h"
#include "neural/layer/affine_t.h"

int main() {
    using namespace SgNet;

    // Tensor inputs(std::vector<int>{1,3,3});
    // inputs.setRandomInt(0,5);

    // Affine_t a(2,std::vector<int>{3,4},0);

    // Tensor out = a.forward(inputs);

    // std::cout<<"after forward\n";

    // std::cout<<"before backward\n";

    // //a.backward(out);

    // std::cout<<"after backward\n";


    // inputs.print();


    // out.print();

    Tensor g(std::vector<int>{3,5});
    g.setRandomInt(0,5);
    g.print();
    g.tranpose2d().print();



}