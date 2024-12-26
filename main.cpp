#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
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

int main() {
    using namespace SgNet;

    Vector aDims(2);
    aDims[0] = 2;
    aDims[1] = 3;

    Vector bDims(2);
    bDims[0] = 3;
    bDims[1] = 2;

    Tensor a(aDims);
    Tensor b(bDims);

    int low = 0;
    int high = 5;

    a.setRandomInt(low,high);
    b.setRandomInt(low,high);

    Tensor out = a.matMult(b);

    a.print();
    std::cout << "\n";
    b.print();
    std::cout << "\n";
    out.print();





}