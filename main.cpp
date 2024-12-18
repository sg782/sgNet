#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"

int main() {

    SgNet::Tensor2d r = SgNet::Tensor2d({5,6});
    SgNet::Tensor2d t = SgNet::Tensor2d({5,6});
    t.print();

    t.setConstant(7);
    t = t / std::vector<double>{-10,10,1,2,3,5};

    t.print();
    SgNet::Tensor2d output = t.transpose();

    t.print();
    output.print();
    
    return 0;
}