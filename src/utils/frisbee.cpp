#include "utils/frisbee.h"
#include <iostream>




SgNet::Frisbee::Frisbee(double*& ref) : ref(ref){

}

void SgNet::Frisbee::operator= (double* newPtr){
    ref = newPtr;
    //return *this;
}
void SgNet::Frisbee::operator= (const double val) const{
    *ref = val;
    //return *this;
}
void SgNet::Frisbee::operator= (const int val) const{ 
    *ref = static_cast<double>(val);
}

void SgNet::Frisbee::operator= (double val){
    *ref = val;
    //return *this;
}
void SgNet::Frisbee::operator= (int val){ 
    *ref = static_cast<double>(val);
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
