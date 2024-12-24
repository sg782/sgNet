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

    Vector v(3);

    v.setConstant(3);

    Tensor r(v);

    r.setRandomGaussian(0,10);

    Vector i = Vector(3);
    i[0] = 1;
    i[1] = 0;
    i[2] = 2;

    r.print();

    std::cout << "\n" << r.at(i).val() << "\n";
     
    return 0;
}