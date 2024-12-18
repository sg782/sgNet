#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"

int main() {

    SgNet::Tensor2d r = SgNet::Tensor2d({5,6});
    SgNet::Tensor2d t = SgNet::Tensor2d({5,6});
    t.print();


    SgNet::Affine<SgNet::Tensor2d> a(2,std::vector<int>{5,3});

    t.setConstant(3);
    SgNet::Tensor2d out = a.forward(t);
    out.print();


    
    return 0;
}