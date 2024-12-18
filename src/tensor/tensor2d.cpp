#include "tensor/tensor2d.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>

SgNet::Tensor2d::Tensor2d(std::vector<int> dims){
    dimensions = dims;

    data = std::vector<std::vector<double>>(dims[0], std::vector<double>(dims[1]));
}

void SgNet::Tensor2d::print(){

    for(int i=0;i<dimensions[0];i++){
        for(int j=0;j<dimensions[1];j++){
            std::cout << data[i][j] << " ";
        }
        std::cout <<"\n";
    }
}


void SgNet::Tensor2d::setConstant(int val){
    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            data[i][j] = val;
        }
    }
}


SgNet::Tensor2d SgNet::Tensor2d::transpose() {
    SgNet::Tensor2d output = SgNet::Tensor2d({this->dimensions[1],this->dimensions[0]});

    for(int i=0;i<this->data.size();i++){
        for(int j=0;j<this->data[0].size();j++){
            output[j][i] = this->data[i][j];
        }
    }
    return output;
}



// rowWise and colwise operations;


// std::vector<std::vector<double>>& SgNet::Tensor2d::byRow(){
//     // returns a list of referenecs to each row vector for us to modify
//     return data;
// }

// std::vector<std::vector<double>>& SgNet::Tensor2d::byCol(){
//     // returns a list of referenecs to each col vector for us to modify
    
// }







/*
BASIC OPERATOR OVERLOADS
    + - * /
*/

// addition overloads
SgNet::Tensor2d SgNet::Tensor2d::operator+ (const double val) const{
    
    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            output[i][j] = this->data[i][j] + val;
        }
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator+ (const std::vector<double> vals) const {
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
        for(int j=0;j<data[0].size();j++){
            output[i][j] = this->data[i][j] + vals[j];
        }
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
        for(int j=0;j<output.dimensions[1];j++){
            output[i][j] = this->data[i][j] + r.data[i][j];
        }
    }

    return output;

}

// subtraction overloads
SgNet::Tensor2d SgNet::Tensor2d::operator- (const double val) const{
    
    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            output[i][j] = this->data[i][j] - val;
        }
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator- (const std::vector<double> vals) const {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
    std::stringstream ss;
    ss << "Subtraction operation cannot be executed on dimensions of ["
        << this->dimensions[0] << ", " << this->dimensions[1] 
        << "] and vector of length " << vals.size() << "!\n";
        throw std::invalid_argument(ss.str());
    }



    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            output[i][j] = this->data[i][j] - vals[j];
        }
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator- (const SgNet::Tensor2d& r) const {

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

    // subtraction
    for(int i=0;i<output.dimensions[0];i++){
        for(int j=0;j<output.dimensions[1];j++){
            output[i][j] = this->data[i][j] - r.data[i][j];
        }
    }

    return output;

}

// multiplication overloads
SgNet::Tensor2d SgNet::Tensor2d::operator* (const double val) const{
    
    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            output[i][j] = this->data[i][j] * val;
        }
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator* (const std::vector<double> vals) const {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
    std::stringstream ss;
    ss << "Multiplication operation cannot be executed on dimensions of ["
        << this->dimensions[0] << ", " << this->dimensions[1] 
        << "] and vector of length " << vals.size() << "!\n";
        throw std::invalid_argument(ss.str());
    }



    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            output[i][j] = this->data[i][j] * vals[j];
        }
    }
    return output;
}

// Matrix On matrix multiplication is NOT elementwise. This could definitely be made clearer 
SgNet::Tensor2d SgNet::Tensor2d::operator* (const SgNet::Tensor2d& r) const {

    // dimension handling
    if(this->dimensions[1]!= r.dimensions[0]){
        std::stringstream ss;
        ss << "Matrix multiplication cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }


    SgNet::Tensor2d output = Tensor2d({this->dimensions[0],r.dimensions[1]});


    // standard matrix multiplication
    /*
    Potential for optimization from naive alg
    */

    for(int i=0;i<output.dimensions[0];i++){
        for(int j=0;j<output.dimensions[1];j++){
            int sum = 0;
            for(int k = 0;k< this->dimensions[1];k++){
                sum += (this->data[i][k] * r.data[k][j]);
            }
            output[i][j] = sum;
        }
    }

    return output;

}

// division overloads
SgNet::Tensor2d SgNet::Tensor2d::operator/ (const double val) const{
    
    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            if(val==0){
                output[i][j] = INFINITY;
                continue;
            }
            output[i][j] = this->data[i][j] / val;
        }
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator/ (const std::vector<double> vals) const {
    // broadcast vector across all rows in tensor

    if(this->dimensions[1]!= vals.size()){
    std::stringstream ss;
    ss << "Division operation cannot be executed on dimensions of ["
        << this->dimensions[0] << ", " << this->dimensions[1] 
        << "] and vector of length " << vals.size() << "!\n";
        throw std::invalid_argument(ss.str());
    }



    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    for(int i=0;i<data.size();i++){
        for(int j=0;j<data[0].size();j++){
            if(vals[j]==0){
                output[i][j] = INFINITY;
                continue;
            }
            output[i][j] = this->data[i][j] / vals[j];
        }
    }
    return output;
}

SgNet::Tensor2d SgNet::Tensor2d::operator/ (const SgNet::Tensor2d& r) const {

    // dimension handling
    if(this->dimensions[0]!= r.dimensions[0] || this->dimensions[1]!= r.dimensions[1]){
        std::stringstream ss;
        ss << "Division operation cannot be executed on dimensions of ["
           << this->dimensions[0] << ", " << this->dimensions[1] 
           << "] and ["
           << r.dimensions[0] << ", " << r.dimensions[1] << "]";
        	throw std::invalid_argument(ss.str());
    }


    SgNet::Tensor2d output = Tensor2d(this->dimensions);

    // addition
    for(int i=0;i<output.dimensions[0];i++){
        for(int j=0;j<output.dimensions[1];j++){
            if(r.data[i][j]==0){
                output[i][j] = INFINITY;
                continue;
            }

            output[i][j] = this->data[i][j] / r.data[i][j];
        }
    }

    return output;

}


// indexing returns a vector (which can be indexed as well)
std::vector<double>& SgNet::Tensor2d::operator[] (int index){
    return this->data[index];
}