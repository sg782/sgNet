#include "tensor/vector.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <vector>




SgNet::Vector::Vector(int size) : data(size,nullptr){
   
}

int SgNet::Vector::size() const{
    return this->data.size();
}

void SgNet::Vector::print(){
    for(int i=0;i<this->size();i++){
        if(data[i]==nullptr){
            std::cout << "null ";
        }else{
            std::cout << *data[i] << " ";
        }
    }
    std::cout << "\n";
}


double SgNet::Vector::dot(const SgNet::Vector& v){
        if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Dot product cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }

    double sum = 0;
    for(int i=0;i<this->size();i++){
        sum += *data[i] * *v[i];
    }
    return sum;
    
}


void SgNet::Vector::setConstant(double val){


    for(int i=0;i<this->size();i++){
        if(data[i]==nullptr){
            data[i] = new double(val);
        }else{
            *data[i] = val;
        }
    }
}

void SgNet::Vector::set(std::vector<double> v){

    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Dot product cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<data.size();i++){
        data[i] = new double(v[i]);
    }

}

void SgNet::Vector::set(SgNet::Vector v){
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Dot product cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<this->size();i++){
        data[i] = new double(*v[i]);
    }
}

SgNet::Vector SgNet::Vector::operator+ (const double val) const{
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        *out[i] = *data[i] + val;
    }
    return out;
}

SgNet::Vector SgNet::Vector::operator+ (const Vector v) const{
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Vector lengths of " << this->size() << " and " << v.size() << " incompatible for addition.\n";
        throw std::invalid_argument(ss.str());
    }

    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){

        *out[i] = *data[i] + *v[i];
    }

    return out;

}


double* SgNet::Vector::operator[] (int index){
    return data[index];
}

const double* SgNet::Vector::operator[] (int index) const{
    return data[index];
}















void SgNet::Vector::operator= (double val){
    this->setConstant(val);
}

void SgNet::Vector::operator= (const std::vector<double> v){
    this->set(v);
}
void SgNet::Vector::operator= (const Vector v){
    this->set(v);
}



