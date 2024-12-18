#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"

int main() {

    SgNet::Tensor2d r = SgNet::Tensor2d({2,3});
    SgNet::Tensor2d t = SgNet::Tensor2d({3,1});

    r.setConstant(1);
    r = r * std::vector<double>{1,2,3};
    r[0][0] = -4;

    t.setConstant(2);
    t[0][0] = 4;


    r.print();
    t.print();

    SgNet::Tensor2d out = r*t;
    out.print();


    
    return 0;
}