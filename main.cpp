#include "tensor/tensor2d.h"

int main() {

    SgNet::Tensor2d r = SgNet::Tensor2d({5,6});
    SgNet::Tensor2d t = SgNet::Tensor2d({5,6});
    t.print();

    r.setConstant(5);

    t.setConstant(7);


    SgNet::Tensor2d output = t / r;


    output.print();

    output = output / 5;
    output.print();

    output = output / std::vector<double>{-10,10,1,2,3,5};
    output.print();

    output = output/0;
    output.print();
    return 0;
}