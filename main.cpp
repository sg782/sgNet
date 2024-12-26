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
    aDims[0] = 4;
    aDims[1] = 4;

    Vector bDims(2);
    bDims[0] = 3;
    bDims[1] = 2;

    Tensor a(aDims);
    Tensor b(bDims);

    a.setConstant(0);
    b.setConstant(1);

    a.print();
    b.print();

    Vector startPoint(2);
    startPoint[0] = 0;
    startPoint[1] = 0;





    Tensor c = a.block(startPoint,b.dims);

    c.copyData(b);

    


    





}