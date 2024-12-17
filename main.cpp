#include "testlib.h"
#include "tensor/tensorNd.h"

int main() {

    SgNet::Tensor t = SgNet::Tensor(2,{10,10});
    t.print();
    return 0;
}