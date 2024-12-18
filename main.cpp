#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"

int main() {

    SgNet::Vector g = SgNet::Vector(3);

    g.setConstant(5);

    g.print();

    g[2] = 1;

    g.print();

    SgNet::Vector out = g / 2;

    out.print();


    
    return 0;
}