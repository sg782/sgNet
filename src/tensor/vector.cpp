#include "tensor/vector.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>

/*
Need to standardize operator= overloads and setter methods


*/



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

void SgNet::Vector::printAddresses(){
    for(int i=0;i<this->size();i++){
        if(data[i]==nullptr){
            std::cout << "null ";
        }else{
            std::cout << data[i].address() << " ";
        }
    }
    std::cout << "\n";
}


void SgNet::Vector::append(double val){
        double* v = new double(val);
        Frisbee f(v);
        data.push_back(f);
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

double SgNet::Vector::product() const{
    double prod = 1;
    for(int i=0;i<data.size();i++){
        prod *= data[i].val();
    }
    return prod;
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


SgNet::Vector SgNet::Vector::copy(){
    SgNet::Vector out(this->size());
    for(int i=0;i<this->size();i++){
        out[i] = new double(data[i].val());
    }

    return out;
}

void SgNet::Vector::copyReferences(SgNet::Vector vals){
    for(int i=0;i<data.size();i++){
        data[i].ref = vals[i].address();
    }
}

SgNet::Vector SgNet::Vector::concat(SgNet::Vector other){
    SgNet::Vector out(this->size() + other.size());

    for(int i=0;i<this->size();i++){
        out[i] = data[i];
    }
    for(int i=0;i<other.size();i++){
        out[i+this->size()] = other[i];
    }

    return out;
}

SgNet::Vector SgNet::Vector::splice(int index, int length){
// add bounds checking later

    SgNet::Vector out(this->size() - length);
    for(int i=0;i<index;i++){
        out[i] = data[i];
    }

    for(int i=index;i<out.size();i++){
        out[i] = data[i+length];
    }

    return out;
}

SgNet::Vector SgNet::Vector::insert(int index,double val){
    // do bounds checking later
    SgNet::Vector out(this->size() + 1);

    for(int i=0;i<index;i++){
        out[i] = data[i];
    }

    out[index] = val;

    for(int i=index+1;i<out.size();i++){
        out[i] = data[i-1];
    }


    return out;
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

SgNet::Vector SgNet::Vector::slice(int startIndex, int endIndex) const{
    int subLength = endIndex - startIndex;
    if(subLength<0){
        // also add bounds control as well
        throw std::invalid_argument("End index must be greater than start index!");
    }
    if(startIndex < 0){
        throw std::invalid_argument("Start Index must be posiive!!!");

    }
    if(endIndex>this->size()){
        throw std::invalid_argument("End index out of bounds!");

    }

    SgNet::Vector out(subLength);
    for(int i=0;i<subLength;i++){
        out[i] = this->operator[](i + startIndex);
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

double SgNet::Vector::dot(const std::vector<int>& v){
        if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Dot product cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }

    double sum = 0;
    for(int i=0;i<this->size();i++){
        sum += data[i].val() * v[i];
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

void SgNet::Vector::setRandomGaussian(double mean, double stdDev){
// https://stackoverflow.com/questions/19944111/creating-a-gaussian-random-generator-with-a-mean-and-standard-deviation
    std::random_device rd;
    
    std::mt19937 e2(rd());

    std::normal_distribution<> dist(mean,stdDev);

    for(int i=0;i<data.size();i++){
        data[i] = dist(e2);
    }


}

void SgNet::Vector::setRandomInt(int low, int high){

    for(int i=0;i<this->size();i++){
        data[i] = low + std::rand() / (RAND_MAX / (high - low + 1) + 1);
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
        if(data[i].val() > val){

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



// operator= : UPDATES the VALUES
// DOES NOT UPDATE MEMORY ADDRESSES
void SgNet::Vector::operator= (double val){
    this->setConstant(val);
}

// operator= : UPDATES the VALUES
// DOES NOT UPDATE MEMORY ADDRESSES
void SgNet::Vector::operator= (const std::vector<double> v){
    this->setValues(v);
}

// operator= : UPDATES the VALUES
// DOES NOT UPDATE MEMORY ADDRESSES
void SgNet::Vector::operator= (const std::vector<int> v){
    this->setValues(v);
}


// // operator= : on a SgNet::Vector
// void SgNet::Vector::operator= (const Vector v){

//     /// not this
//     this->setValues(v);
// }


// setValues(std::vector) : UPDATES the VALUES
// DOES NOT UPDATE MEMORY ADDRESSES
void SgNet::Vector::setValues(std::vector<double> v){

    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "SetValues with SgNet::Vector cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }
    // setValues
    for(int i=0;i<this->size();i++){
        if(data[i]==nullptr){
            data[i] = new double(v[i]);
        }else{
            *data[i] = v[i];
        }
    }
}

// setValues(std::vector) : UPDATES the VALUES
// DOES NOT UPDATE MEMORY ADDRESSES
void SgNet::Vector::setValues(std::vector<int> v){

    if(data.size() != v.size()){
        std::stringstream ss;
        ss << "SetValues with SgNet::Vector cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }
    // setValues
    for(int i=0;i<this->size();i++){
        if(data[i]==nullptr){
            data[i] = new double(v[i]);
        }else{
            *data[i] = v[i];
        }
    }
}

// setValues(std::vector) : UPDATES the VALUES
// DOES NOT UPDATE MEMORY ADDRESSES
void SgNet::Vector::setValues(SgNet::Vector v){
    // copies values 
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "SetValues with SgNet::Vector cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<this->size();i++){
        if(data[i]==nullptr){
            data[i] = new double(v[i].val());
        }else{
            data[i] = v[i].val();
        }
    }

}


// set(std::vector) : CREATES new MEMORY AND VALUE
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

// set(std::vector) : CREATES new MEMORY AND VALUE
void SgNet::Vector::set(std::vector<int> v){

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

// set(std::vector) : CREATES new MEMORY AND VALUE
void SgNet::Vector::set(SgNet::Vector v){
    // CREATES and returns NEW MEMORY
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


// overwrite(std::vector) : OVERWRITES CURRENT VECTOR WITH THE DATA OF NEW VECTOR
// REPLACES FRISBEE VALUES, both vectors now share the EXACT SAME memory (in each frisbee)
void SgNet::Vector::overwrite(SgNet::Vector v){
    // OVERWRITES
    // overwrites the data in a vector
    if(this->size() != v.size()){
        std::stringstream ss;
        ss << "Set with SgNet::Vector cannot be executed on dimensions of "
           << this->size() << " and " << v.size() << "\n";
        throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<this->size();i++){
        data[i] = v[i];
    }
}







/*
In the context of data passing operations, we need 3 different types of methods
1. Purely updates the values 
2. Updates the reference
3. replaces with same frisbee object




*/