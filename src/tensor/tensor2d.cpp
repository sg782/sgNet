#include "tensor/tensor2d.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "tensor/vector.h"
#include <array>


/*

About half of the operations are converted to use the new vector class. This is enough to be able to implement the rowwise and colwise methods.


*/

SgNet::Tensor2d::Tensor2d(std::vector<int> dims){
    dimensions = dims;
    
    data = std::vector<SgNet::Vector>(dims[0],SgNet::Vector(dims[1]));
    for(int i=0;i<data.size();i++){
        data[i] = SgNet::Vector(dims[1]);
    }

}

void SgNet::Tensor2d::print(){

    for(int i=0;i<dimensions[0];i++){
        data[i].print();
    }
}

std::array<int,2> SgNet::Tensor2d::shape() const{
    std::array<int,2> out;
    out[0] = data.size();
    out[1] = data[0].size();
    return out;
}

void SgNet::Tensor2d::printShape() const{
    std::array<int,2> out = this->shape();

    std::cout << "[" << out[0] << ", " << out[1] << "]\n";
}


double SgNet::Tensor2d::sum() const{
    double sum;
    for(int i=0;i<data.size();i++){
        sum += data[i].sum();
    }
    return sum;
}
SgNet::Vector SgNet::Tensor2d::rowSum(){
    Vector sum(data.size());
    for(int i=0;i<data.size();i++){
        sum[i] = data[i].sum();
    }
    return sum;
}

SgNet::Vector SgNet::Tensor2d::colSum(){
    Tensor2d thisCol = this->byCol();
    return thisCol.rowSum();
}




int SgNet::Tensor2d::numRows(){
    return data.size();
}
int SgNet::Tensor2d::numCols(){
    return data[0].size();
}


void SgNet::Tensor2d::setConstant(double val){
    for(int i=0;i<data.size();i++){
        data[i].setConstant(val);
    }
}

void SgNet::Tensor2d::setRandom(double mean, double stdDev){
    for(int i=0;i<data.size();i++){
        data[i].setRandom(mean,stdDev);
    }
}


SgNet::Tensor2d SgNet::Tensor2d::matMult(SgNet::Tensor2d b){

    // dimension handling
    if(this->dimensions[1]!= b.dimensions[0]){
        std::stringstream ss;
        ss << "Matrix multiplication cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << b.dimensions[0] << ", " << b.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }


    SgNet::Tensor2d output = Tensor2d({this->dimensions[0],b.dimensions[1]});


    // standard matrix multiplication
    /*
    Potential for optimization from naive alg
    */

    for(int i=0;i<output.dimensions[0];i++){
        for(int j=0;j<output.dimensions[1];j++){
            output[i][j] = this->operator[](i).dot(b.byCol()[j]);
        }
    }

    return output;

}



SgNet::Tensor2d SgNet::Tensor2d::transpose() {
    // tranpose makes a copy
    SgNet::Tensor2d output = SgNet::Tensor2d({this->dimensions[1],this->dimensions[0]});

    for(int i=0;i<this->data.size();i++){
        for(int j=0;j<this->data[0].size();j++){
            output[j][i] = new double(*data[i][j]);
        }
    }
    return output;
}



// rowWise and colwise operations;


SgNet::Tensor2d SgNet::Tensor2d::byRow(){
    // returns a list of referenecs to each row vector for us to modify

    // maybe this is a little incorrect. We are not wanting to return the same object,
    // just a tensor as row major
    return *this;
}

SgNet::Tensor2d SgNet::Tensor2d::byCol(){
    // returns a list of referenecs to each col vector for us to modify

    // we are essentially transposing, but we want to have original memory locations accessible
    int rows = data[0].size();
    int cols = data.size();
    SgNet::Tensor2d out({rows,cols});

    // references to each memory location, but in colwise form
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            out[j][i] = data[i][j];
        }
    }

    return out;
}







/*
BASIC OPERATOR OVERLOADS
    + - * /

    this was tedious, do not recommend
*/

// addition overloads
SgNet::Tensor2d SgNet::Tensor2d::operator+ (const double val) const{
    
    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        output[i] = data[i] + val;
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator+ (const SgNet::Vector& vals) const {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
        std::stringstream ss;
        ss << "Addition operation cannot be executed on dimensions of ["
            << this->dimensions[0] << ", " << this->dimensions[1] 
            << "] and vector of length " << vals.size() << "\n";
            throw std::invalid_argument(ss.str());
    }

    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        output[i] = data[i] + vals;
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator+ (const SgNet::Tensor2d& r) const {

    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Addition operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }

    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    // addition
    for(int i=0;i<output.dimensions[0];i++){
        // adding each row
        output[i] = data[i] + r.data[i];
    }
    return output;
}

void SgNet::Tensor2d::operator+= (const double val){
    for(int i=0;i<this->data.size();i++){
        data[i] += val;
    }
}

void SgNet::Tensor2d::operator+= (const Vector& vals) {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
        std::stringstream ss;
        ss << "Addition operation cannot be executed on dimensions of ["
            << this->dimensions[0] << ", " << this->dimensions[1] 
            << "] and vector of length " << vals.size() << "\n";
            throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<data.size();i++){
        data[i] += vals;
    }

    this->print();
}

void SgNet::Tensor2d::operator+= (const Tensor2d& r){

    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Addition operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }
    // addition
    for(int i=0;i<data.size();i++){
        // adding each row
        data[i] += r.data[i];
    }

}


// subtraction overloads
SgNet::Tensor2d SgNet::Tensor2d::operator- (const double val) const{
    
    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        output[i] = data[i] - val;
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator- (const SgNet::Vector& vals) const {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
        std::stringstream ss;
        ss << "Subtraction operation cannot be executed on dimensions of ["
            << this->dimensions[0] << ", " << this->dimensions[1] 
            << "] and vector of length " << vals.size() << "\n";
            throw std::invalid_argument(ss.str());
    }

    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        output[i] = data[i] - vals;
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator- (const SgNet::Tensor2d& r) const {

    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Subtraction operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }

    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    // addition
    for(int i=0;i<output.dimensions[0];i++){
        // adding each row
        output[i] = data[i] - r.data[i];
    }
    return output;
}

void SgNet::Tensor2d::operator-= (const double val){
    for(int i=0;i<this->data.size();i++){
        data[i] -= val;
    }
}

void SgNet::Tensor2d::operator-= (const Vector& vals) {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
        std::stringstream ss;
        ss << "Subtraction operation cannot be executed on dimensions of ["
            << this->dimensions[0] << ", " << this->dimensions[1] 
            << "] and vector of length " << vals.size() << "\n";
            throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<data.size();i++){
        data[i] -= vals;
    }
}

void SgNet::Tensor2d::operator-= (const Tensor2d& r){

    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Subtraction operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }
    // addition
    for(int i=0;i<data.size();i++){
        // adding each row
        data[i] -= r.data[i];
    }

}



// multiplication overloads
SgNet::Tensor2d SgNet::Tensor2d::operator* (const double val) const{
    
    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        output[i] = data[i] * val;
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator* (const SgNet::Vector& vals) const {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
        std::stringstream ss;
        ss << "Multiplication operation cannot be executed on dimensions of ["
            << this->dimensions[0] << ", " << this->dimensions[1] 
            << "] and vector of length " << vals.size() << "\n";
            throw std::invalid_argument(ss.str());
    }

    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        output[i] = data[i] * vals;
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator* (const SgNet::Tensor2d& r) const {

    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Multiplication operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }

    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    // addition
    for(int i=0;i<output.dimensions[0];i++){
        // adding each row
        output[i] = data[i] * r.data[i];
    }
    return output;
}

void SgNet::Tensor2d::operator*= (const double val){
    for(int i=0;i<this->data.size();i++){
        data[i] *= val;
    }
}

void SgNet::Tensor2d::operator*= (const Vector& vals) {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
        std::stringstream ss;
        ss << "Multiplication operation cannot be executed on dimensions of ["
            << this->dimensions[0] << ", " << this->dimensions[1] 
            << "] and vector of length " << vals.size() << "\n";
            throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<data.size();i++){
        data[i] *= vals;
    }
}

void SgNet::Tensor2d::operator*= (const Tensor2d& r){

    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Multiplication operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }
    // addition
    for(int i=0;i<data.size();i++){
        // adding each row
        data[i] *= r.data[i];
    }

}


// divison overloads
SgNet::Tensor2d SgNet::Tensor2d::operator/ (const double val) const{
    
    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        if(val==0){
            output[i] = INFINITY;
            continue;
        }
        output[i] = data[i] / val;
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator/ (const SgNet::Vector& vals) const {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
        std::stringstream ss;
        ss << "Multiplication operation cannot be executed on dimensions of ["
            << this->dimensions[0] << ", " << this->dimensions[1] 
            << "] and vector of length " << vals.size() << "\n";
            throw std::invalid_argument(ss.str());
    }

    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        output[i] = data[i] / vals;
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator/ (const SgNet::Tensor2d& r) const {

    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Multiplication operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }

    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    // addition
    for(int i=0;i<output.dimensions[0];i++){
        // adding each row
        output[i] = data[i] / r.data[i];
    }
    return output;
}

void SgNet::Tensor2d::operator/= (const double val){
    for(int i=0;i<this->data.size();i++){
        data[i] /= val;
    }
}

void SgNet::Tensor2d::operator/= (const Vector& vals) {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
        std::stringstream ss;
        ss << "Division operation cannot be executed on dimensions of ["
            << this->dimensions[0] << ", " << this->dimensions[1] 
            << "] and vector of length " << vals.size() << "\n";
            throw std::invalid_argument(ss.str());
    }

    for(int i=0;i<data.size();i++){
        data[i] /= vals;
    }
}

void SgNet::Tensor2d::operator/= (const Tensor2d& r){
    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Division operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }
    // addition
    for(int i=0;i<data.size();i++){
        // adding each row
        data[i] /= r.data[i];
    }

}



// indexing returns a vector (which can be indexed as well)
SgNet::Vector& SgNet::Tensor2d::operator[] (int index){
    return this->data[index];
}