#include "utils/frisbee.h"
#include <iostream>




SgNet::Frisbee::Frisbee(double*& ref) : ref(ref){

}

void SgNet::Frisbee::operator= (double* newPtr){
    ref = newPtr;
    //return *this;
}
void SgNet::Frisbee::operator= (double val){
    *ref = val;
    //return *this;
}

double& SgNet::Frisbee::operator*() {
    return *ref;
}

const double SgNet::Frisbee::val() const{
    return(*ref);
}



bool SgNet::Frisbee::operator==(double* val){
    return(ref==val);
}

void SgNet::Frisbee::printValue(){
    std::cout << *ref << "\n";
}
void SgNet::Frisbee::printAddress(){
    std::cout << ref << "\n";
}
