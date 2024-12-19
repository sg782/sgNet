#include "tensor/tensor2d.h"
#include "neural/layer/affine.h"
#include "tensor/vector.h"
#include "utils/frisbee.h"
#include <iostream>

int main() {

   using namespace SgNet;


    double* var = new double(5.0);


   Frisbee g = Frisbee(var);

   g.print();
   g.printAddress();

   g = 20;
   
   g.print();
   g.printAddress();

   std::cout << var << "\n";

     
    return 0;
}