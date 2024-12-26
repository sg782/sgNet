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

    // Vector aDims(3);
    // aDims = 4;
    

    // Vector bDims(3);
    // bDims[0] = 3;
    // bDims[1] = 2;
    // bDims[2] = 3;

    // Tensor a(aDims);
    // Tensor b(bDims);

    // a.setConstant(0);
    // b.setConstant(1);

    // a.print();
    // b.print();

    // Vector startPoint(3);
    // startPoint[0] = 1;
    // startPoint[1] = 1;
    // startPoint[2] = 1;

    // a.print();

    // b.print();

    // a.block(startPoint,b.dims).copyData(b);

   
    // a.print();

    // b.print();


    Vector aDims(3);
    aDims = 4;

    Tensor a(aDims);
    a.setConstant(5);

    Tensor b(aDims);
    b.setConstant(2);

    a-=b;

    a.print();





    





}