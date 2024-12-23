#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>
#include "neural/layer/softmax.h"
#include "neural/loss/categoricalCrossEntropy.h"

int main() {
    using namespace SgNet;

    Tensor2d t = Tensor2d({2,5});
    Vector labels = Vector(2);
    labels[0] = 1;
    labels[1] = 2;
    t.setRandom(0,10);

    Softmax s = Softmax(5);

    CCE l = CCE();



    Tensor2d out = s.forward(t);

    double loss = l.calculate(out,labels);

    Tensor2d back = l.backward(out,labels);

    // just checking for running

    std::cout << loss << "\n";
    t.print();
    out.print();
    back.print();

     
    return 0;
}