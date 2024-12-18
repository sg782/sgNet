#include "tensor/tensor2d.h"

int main() {

    SgNet::Tensor2d r = SgNet::Tensor2d({5,6});
    SgNet::Tensor2d t = SgNet::Tensor2d({5,6});
    t.print();

    r.setConstant(5);

    t.setConstant(7);
    t[1][2] = 5;

    SgNet::Tensor2d output = t + r;
    output.print();
    return 0;
}