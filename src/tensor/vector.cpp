#include "tensor/vector.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>





SgNet::Vector::Vector(int size) : data(size){
    for(int i=0;i<size;i++){
        data[i] = new double(0);
    }
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

void SgNet::Vector::resize(int newSize){
    data.resize(newSize);
}

double SgNet::Vector::sum() const{
    double sum = 0;
    for(int i=0;i<data.size();i++){
        sum += data[i].val();
    }
    return sum;
}

void SgNet::Vector::max(double val){
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() > val){
            this->operator[](i) = val;
        }
    }
}

double SgNet::Vector::max(){
    double maxVal = -INFINITY;
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() > maxVal){
            maxVal = this->operator[](i).val();
        }
    }
    return maxVal;
}


void SgNet::Vector::min(double val){
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() < val){
            this->operator[](i) = val;
        }
    }
}

double SgNet::Vector::min(){
    double minVal = INFINITY;
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() < minVal){
            minVal = this->operator[](i).val();
        }
    }
    return minVal;
}

SgNet::Vector SgNet::Vector::exp() const{
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        out[i] = std::exp(this->operator[](i).val());
    }
    return out;
}

SgNet::Vector SgNet::Vector::square() const{
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        double val = this->operator[](i).val();
        out[i] = val*val;
    }
    return out;
}

SgNet::Vector SgNet::Vector::tanh() const{
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        double val = this->operator[](i).val();
        double ePlusX = std::exp(val);
        double eMinusX  = std::exp(-val);

        out[i] = (ePlusX - eMinusX) / (ePlusX + eMinusX);
    }
    return out;
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
        sum += data[i].val() * v[i].val();
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

void SgNet::Vector::setRandom(double mean, double stdDev){
// https://stackoverflow.com/questions/19944111/creating-a-gaussian-random-generator-with-a-mean-and-standard-deviation
    std::random_device rd;
    
    std::mt19937 e2(rd());

    std::normal_distribution<> dist(mean,stdDev);

    for(int i=0;i<data.size();i++){
        data[i] = dist(e2);
    }


}

void SgNet::Vector::set(std::vector<double> v){

    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Set with std::vector cannot be executed on dimensions of "
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
        ss << "Set with SgNet::Vector cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<this->size();i++){
        data[i] = new double(*v[i]);
    }
}


// standard numeric operations

// Addition
SgNet::Vector SgNet::Vector::operator+ (const double val) const{
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        out[i] = data[i].val() + val;
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

        out[i] = data[i].val() + v[i].val();
    }

    return out;
}
void SgNet::Vector::operator+= (const double val){
    for(int i=0;i<this->size();i++){
        data[i] = data[i].val() + val;
    }
}
void SgNet::Vector::operator+= (const Vector v){
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Vector lengths of " << this->size() << " and " << v.size() << " incompatible for addition.\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<this->size();i++){
        data[i] = data[i].val() + v[i].val();
    }

}


// Subtraction
SgNet::Vector SgNet::Vector::operator- (const double val) const{
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        out[i] = data[i].val() - val;
    }
    return out;
}
SgNet::Vector SgNet::Vector::operator- (const Vector v) const{
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Vector lengths of " << this->size() << " and " << v.size() << " incompatible for subtraction.\n";
        throw std::invalid_argument(ss.str());
    }

    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){

        out[i] = data[i].val() - v[i].val();
    }

    return out;

}
void SgNet::Vector::operator-= (const double val){
    for(int i=0;i<this->size();i++){
        data[i] = data[i].val() - val;
    }
}
void SgNet::Vector::operator-= (const Vector v){
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Vector lengths of " << this->size() << " and " << v.size() << " incompatible for subtraction.\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<this->size();i++){
        data[i] = data[i].val() - v[i].val();
    }

}


// Multiplication
SgNet::Vector SgNet::Vector::operator* (const double val) const{
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        out[i] = data[i].val() * val;
    }
    return out;
}
SgNet::Vector SgNet::Vector::operator* (const Vector v) const{
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Vector lengths of " << this->size() << " and " << v.size() << " incompatible for addition.\n";
        throw std::invalid_argument(ss.str());
    }

    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){

        out[i] = data[i].val() * v[i].val();
    }

    return out;

}
void SgNet::Vector::operator*= (const double val){
    for(int i=0;i<this->size();i++){
        data[i] = data[i].val() * val;
    }
}
void SgNet::Vector::operator*= (const Vector v){
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Vector lengths of " << this->size() << " and " << v.size() << " incompatible for multiplication.\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<this->size();i++){
        data[i] = data[i].val() * v[i].val();
    }

}



// Division
SgNet::Vector SgNet::Vector::operator/ (const double val) const{
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        if(data[i].val()==0){
            out[i] = INFINITY;
            continue;
        }
        out[i] = data[i].val() / val;
    }
    return out;
}
SgNet::Vector SgNet::Vector::operator/ (const Vector v) const{
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Vector lengths of " << this->size() << " and " << v.size() << " incompatible for addition.\n";
        throw std::invalid_argument(ss.str());
    }

    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        if(data[i].val()==0){
            out[i] = INFINITY;
            continue;
        }

        out[i] = data[i].val() / v[i].val();
    }

    return out;

}
void SgNet::Vector::operator/= (const double val){
    for(int i=0;i<this->size();i++){
        data[i] = data[i].val() / val;
    }
}
void SgNet::Vector::operator/= (const Vector v){
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Vector lengths of " << this->size() << " and " << v.size() << " incompatible for division.\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<this->size();i++){
        data[i] = data[i].val() / v[i].val();
    }

}




SgNet::Vector SgNet::Vector::operator< (const double val) const{
    Vector out = Vector(this->size());
    out.setConstant(0);
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() < val){
            out[i] = 1;
        }
    }
    return out;
}
SgNet::Vector SgNet::Vector::operator< (const SgNet::Vector vals) const{
    Vector out = Vector(this->size());
    out.setConstant(0);
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() < vals[i].val()){
            out[i] = 1;
        }
    }
    return out;

}
SgNet::Vector SgNet::Vector::operator<= (const double val) const{
    Vector out = Vector(this->size());
    out.setConstant(0);
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() <= val){
            out[i] = 1;
        }
    }
    return out;
}
SgNet::Vector SgNet::Vector::operator<= (const SgNet::Vector vals) const{
    Vector out = Vector(this->size());
    out.setConstant(0);
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() <= vals[i].val()){
            out[i] = 1;
        }
    }
    return out;
}


SgNet::Vector SgNet::Vector::operator> (const double val) const{
    Vector out = Vector(this->size());
    out.setConstant(0);
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() > val){
            out[i] = 1;
        }
    }
    return out;

}
SgNet::Vector SgNet::Vector::operator> (const SgNet::Vector vals) const{
    Vector out = Vector(this->size());
    out.setConstant(0);
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() > vals[i].val()){
            out[i] = 1;
        }
    }
    return out;
}
SgNet::Vector SgNet::Vector::operator>= (const double val) const{
    Vector out = Vector(this->size());
    out.setConstant(0);
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() >= val){
            out[i] = 1;
        }
    }
    return out;
}
SgNet::Vector SgNet::Vector::operator>= (const SgNet::Vector vals) const{
    Vector out = Vector(this->size());
    out.setConstant(0);
    for(int i=0;i<this->size();i++){
        if(this->operator[](i).val() >= vals[i].val()){
            out[i] = 1;
        }
    }
    return out;
}



SgNet::Frisbee& SgNet::Vector::operator[] (int index){
    return data[index];
}

const SgNet::Frisbee& SgNet::Vector::operator[] (int index) const{
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



