#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>
#include "neural/layer/softmax.h"
#include "neural/loss/categoricalCrossEntropy.h"
#include "utils/fileReading.h"

int main() {
    using namespace SgNet;

    Tensor2d data({10,784});
    Vector labels({10});

    loadData(data,labels,10);

    data.print();

    labels.print();

     
    return 0;
}