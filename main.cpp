#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include <iostream>

int main() {

    SgNet::Tensor2d a = SgNet::Tensor2d({3,4});

    SgNet::Vector b = SgNet::Vector(3);

    b.setConstant(1);
    std::cout << b[0];
    
    a.setConstant(3);

    std::cout<<a[0][0];

    a.print();


     
    return 0;
}