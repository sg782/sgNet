#include "tensor/tensor.h"
#include "tensor/vector.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "utils/frisbee.h"
#include <initializer_list>
#include "tensor/tensor2d.h"

SgNet::Tensor::Tensor(Vector dims){
    nDims = dims.size();
    this->dims.resize(nDims);
    this->dims = dims;

    this->setIndexDims();

    flatLength = static_cast<int>(dims.product());
    data.resize(flatLength);
    data = Vector(flatLength);
}

SgNet::Tensor::Tensor(
    std::vector<double> dims
    ){
    // vector should be of type int. I just dont want to add more overloads rn 
    
    nDims = dims.size();
    this->dims.resize(nDims);
    this->dims.set(dims);

    this->setIndexDims();

    flatLength = static_cast<int>(this->dims.product());
    data.resize(flatLength);
    data = Vector(flatLength);
}

SgNet::Tensor::Tensor(
    std::vector<int> dims
    ){
    // vector should be of type int. I just dont want to add more overloads rn 

    this->nDims = dims.size();

    this->dims.resize(nDims);

    this->dims.setValues(dims);

    this->setIndexDims();

    flatLength = static_cast<int>(this->dims.product());
    data.resize(flatLength);

    data = Vector(flatLength);
}

SgNet::Tensor::Tensor(
    std::initializer_list<int> dims
    ){
    // vector should be of type int. I just dont want to add more overloads rn 
    
    nDims = dims.size();
    this->dims.resize(nDims);
    this->dims.set(dims);

    this->setIndexDims();

    flatLength = static_cast<int>(this->dims.product());
    data.resize(flatLength);
    data = Vector(flatLength);
}

double SgNet::Tensor::sum() const{
    return data.sum();
}

int SgNet::Tensor::getDim(int idx) const{
    return static_cast<int>(dims[idx].val());
}





SgNet::Vector SgNet::Tensor::axisSum(int axis){
    int axisWidth = this->getDim(axis);
    SgNet::Vector out(axisWidth);

    for(int i=0;i<axisWidth;i++){
        out[i] = this->getAxis(axis,i).sum();
    }
    return out;
}

void SgNet::Tensor::setIndexDims(){
    indexDims.resize(nDims);
    indexDims.setConstant(1);
    for(int i=dims.size()-2;i>=0;i--){
        indexDims[i] = indexDims[i+1].val() * dims[i+1].val();
    }
}


void SgNet::Tensor::setConstant(double val){
    data.setConstant(val);
}

void SgNet::Tensor::setRandomGaussian(double mean, double stdDev){
    data.setRandomGaussian(mean,stdDev);
}

void SgNet::Tensor::setRandomInt(int low, int high){
    data.setRandomInt(low,high);
}

SgNet::Tensor SgNet::Tensor::matMult(SgNet::Tensor b){

    // check that these are 2dimensional
    if(nDims!= 2 || b.nDims!=2){
        throw std::runtime_error("Matrix Multiplication requires 2d tensors");
    }

    // check validity
    if(this->dims[1].val() != b.dims[0].val()){
        std::stringstream ss;
        ss << "Matrix multiplication cannot be executed on dimensions of ["
           << this->dims[0].val() << ", " << this->dims[1].val()
           << "] and ["
           << b.dims[0].val() << ", " << b.dims[1].val() << "]";
        	throw std::invalid_argument(ss.str());
    }



    Vector outDims(2);
    outDims[0] = this->dims[0].val();
    outDims[1] = b.dims[1].val();

    Tensor out(outDims);

    // since we know that 'out' is 2 dimensional, we can explicitly index over it
    // instead of calling the getDimensional index function

    for(int i=0;i<out.dims[0].val();i++){
        for(int j=0;j<out.dims[1].val();j++){
            // we will explicitly index instead of doing the overloaded tensor index
            // should avoid wasting memory

            // lots of method calls here
            out.data[(i*out.dims[1].val())+j] = this->getAxis(0,i).asVector().dot(b.getAxis(1,j).asVector());
        }
    }

    return out;
}

SgNet::Vector SgNet::Tensor::getDimensionalIndex(int index){
    Vector out(nDims);

    for(int i=0;i<nDims;i++){
        int idx = index / indexDims[i].val();
        out[i] = idx;
        index -= (idx * indexDims[i].val());
    }

    return out;
}

SgNet::Vector SgNet::Tensor::asVector(){
    // maybe this should return the actual values
    return data;
}

SgNet::Tensor SgNet::Tensor::block(SgNet::Vector startPoint, SgNet::Vector blockDims){
    SgNet::Tensor out(blockDims);

    for(int i=0;i<out.flatLength;i++){
        /*
        out[i]: get it from using the startpoint, plus the dimensionalIndex, dotted with tensor's indexDims

        steps happening:
        1. convert 'i' into the dimensional index (what the index would be if the tensor were truly the shape it is defined)
        2. add the dimensional index with the start point, to get where in the original tensor we are currently indexing
        3. translate it back to a flat coordinate, by finding its dotproduct with indexDims
        4. use the flat coordinate to index the original
        */
       out.data[i] = data[(startPoint+out.getDimensionalIndex(i)).dot(indexDims)];
    }

    return out;
}

// add a byAxis() method, that lets us index by that axis
SgNet::Tensor SgNet::Tensor::getAxis(int axis, int index){
    // 0 indexed
    SgNet::Vector newDims = dims.splice(axis,1).copy();

    SgNet::Tensor out(newDims);


    // this indices are computed as follows
    /*
    - using the indexDims   
    - as if we are iterating over the properly dimensioned arrays   

    multiply each index by it's cooresponding indexDim value from original tensor, always leaving the relevant axis index equal to index

    */

   // i hope this ends up being an efficient way to do this, because it is sleek!
    for(int i=0;i<out.flatLength;i++){
        double idx = out.getDimensionalIndex(i).insert(axis,index).dot(indexDims);
        out.data[i] = data[static_cast<int>(idx)];
    }
    return out;
}

SgNet::Frisbee SgNet::Tensor::at(int index){
    if(nDims != 1){
        std::stringstream ss;
        ss << "Tensor has " << nDims << " dimensions. Use the Vector-based overload. Integer overload is only for one dimensional vectors.";
        throw std::invalid_argument(ss.str());
    }

    return data[index];
}

SgNet::Frisbee SgNet::Tensor::at(SgNet::Vector indices){
    // add dimensions checks

    if(nDims != indices.size()){
        std::stringstream ss;
        ss << "index vector is not of length " << nDims << "\n";
        throw std::invalid_argument(ss.str());
    }

    double dbIdx = indexDims.dot(indices);
    int index = static_cast<int>(dbIdx);

    return data[index];
}

SgNet::Frisbee SgNet::Tensor::at(std::vector<int> indices){
    // add dimensions checks

    SgNet::Vector mIndices(nDims);
    mIndices = indices;

    if(nDims != indices.size()){
        std::stringstream ss;
        ss << "index vector is not of length " << nDims << "\n";
        throw std::invalid_argument(ss.str());
    }

    double dbIdx = indexDims.dot(mIndices);
    int index = static_cast<int>(dbIdx);

    return data[index];
}

SgNet::Tensor SgNet::Tensor::tensorAt(SgNet::Vector indices){
    // do bounds checking later

    // uncompleted method to return a tensor at a given index. im pretty sure this is just gonna be a fancy getAxis() method, just with explicit indexing, which we dont need.
    
    int Isize = indices.size();

    SgNet::Tensor out(dims.slice(Isize,nDims));

    int nRemainingData = out.dims.product();

    int startIndex = indexDims.slice(0,Isize).dot(indices);

    out.data = (data.slice(startIndex,startIndex+nRemainingData));

    return out;

}


void SgNet::Tensor::setData(Vector newData){
    if(newData.size()!=flatLength){
        // error
    }

    data = newData;
}

void SgNet::Tensor::copyData(SgNet::Tensor other){

    data.setValues(other.data);
}

void SgNet::Tensor::copyData(SgNet::Tensor2d other){
    if(flatLength!=other.numRows()*other.numCols()){
        throw std::invalid_argument("Tensors not of compatible volumes");
    }

    for(int i=0;i<other.numRows();i++){
        for(int j=0;j<other.numCols();j++){
            data[i*other.numCols() + j] = other[i][j].val();
        }
    }
}



void SgNet::Tensor::print(){
    std::vector<int> printDims = std::vector<int>(nDims);
    
    printDims[nDims - 1] = dims[nDims -1].val();
    for(int i=nDims-2;i>=0;i--){
        printDims[i] = printDims[i+1] * dims[i].val();
    }
    for(int i=0;i<flatLength;i++){
        for(int j=0;j<printDims.size();j++){
            if(i % printDims[j] == 0){
                std::cout << "\n";
            }
        }
        std::cout << data[i].val() << " ";
    }
    std::cout << "\n";
}

void SgNet::Tensor::printShape(){
    this->dims.print();
}

SgNet::Tensor SgNet::Tensor::operator[](int index){

    if(nDims<1){
        throw std::invalid_argument("you indexed too far !!!");
    }
    if(nDims==1){
        // maybe make a custom handling for 0 dimension tensors so they have just one value
    }
    // the [] operator will return a Tensor with dim of nDims - 1. We are indexing the largest index, so it would be dims[0], thus our resulting dim is dims.slice(1,dims.size())

    // how to handle the case where the tensor has 1 dimension, and indexing it (should) just return a value?
    // all i can think of is 


    SgNet::Vector newDims = dims.slice(1,dims.size());

    int startIdx = index * newDims.product();
    int endIdx = (index+1)*newDims.product();

    // maybe for efficiency, we make a setData, function which just sets the data of the new tensor to be pointing to the same memory as the data, instead of doing that manually in a loop
    

    SgNet::Tensor out(newDims);

    // this is where our issue is (i think resolved);
    out.data.overwrite(data.slice(startIdx,endIdx));

    return out;
}

const SgNet::Tensor SgNet::Tensor::operator[] (int index) const{
    
    SgNet::Vector newDims = dims.slice(1,dims.size());

    int startIdx = index * newDims.product();
    int endIdx = (index+1)*newDims.product();


    // maybe for efficiency, we make a setData, function which just sets the data of the new tensor to be pointing to the same memory as the data, instead of doing that manually in a loop
    

    SgNet::Tensor out(newDims);
    out.setData(data.slice(startIdx,endIdx));

    return out;
}

//transpose makes a copy
SgNet::Tensor SgNet::Tensor::transpose2d(){
    
    //assert dims is 2
    if(nDims!= 2){
        throw std::runtime_error("transpose2d requires 2d tensors");
    }

    Tensor out(std::vector<int>{this->getDim(1),this->getDim(0)});


    for(int i=0;i<out.getDim(0);i++){
        for(int j=0;j<out.getDim(1);j++){
            out.at(std::vector<int>{i,j}) = this->at(std::vector<int>{j,i}).val();
        }
    }
    return out;

}


/*
MORE OVERLOADS WILL BE ADDED AS THEY BECOME NECESSARY. I DONT NOT WANT TO DO ALL 30+ RIGHT NOW

*/

// addition overloads
SgNet::Tensor SgNet::Tensor::operator+ (const double val) const{
    SgNet::Tensor output = Tensor(this->dims);
    output.setData(data+val);    
    return output;
}
void SgNet::Tensor::operator+= (const double val){
    data += val;
}
void SgNet::Tensor::operator+= (Vector v){
    if(v.size()!=dims[dims.size()-1].val()){
        throw std::runtime_error("Vector length does not match the innermost dimension");
    }

    for(int i=0;i<dims[0].val();i++){
        this->operator[](i) += v[i].val();;
    }

}


// subtraction overloads
SgNet::Tensor SgNet::Tensor::operator- (const double val) const{
    SgNet::Tensor output = Tensor(this->dims);
    output.setData(data-val);    
    return output;
}
void SgNet::Tensor::operator-= (const double val){
    data -= val;
}
void SgNet::Tensor::operator-=(Tensor other){
    data -= other.data;
}

// multiplication overloads
SgNet::Tensor SgNet::Tensor::operator* (const double val) const{
    SgNet::Tensor output = Tensor(this->dims);
    output.setData(data*val);    
    return output;
}
void SgNet::Tensor::operator*= (const double val){
    data *= val;
}
void SgNet::Tensor::operator*=(Tensor other){
    data *= other.data;
}

// SgNet::Tensor SgNet::Tensor::operator* (Tensor other){

// }

// division overloads
SgNet::Tensor SgNet::Tensor::operator/ (const double val) const{
    SgNet::Tensor output = Tensor(this->dims);
    output.setData(data/val);    
    return output;
}
void SgNet::Tensor::operator/= (const double val){
    data /= val;
}
void SgNet::Tensor::operator= (Tensor b){
    // pretty much just puts tensor b in the place of this



    if(b.data.size()!=flatLength){
    // error
    }
    
    nDims = b.nDims;
    
    this->dims.resize(nDims);
    this->dims = b.dims.copy();

    this->setIndexDims();

    flatLength = static_cast<int>(dims.product());
    data.resize(flatLength);
    data = Vector(flatLength);
    data.copyReferences(b.data);
}


SgNet::Tensor SgNet::Tensor::operator> (double val){
    Tensor out(this->dims);
    out.data = (data>0);

    return out;
}

SgNet::Tensor SgNet::Tensor::operator<= (double val){
    Tensor out(this->dims);
    out.data = (data<=0);

    return out;
}

SgNet::Tensor SgNet::Tensor::operator* (SgNet::Tensor b){

    // bounds checking
    if(this->flatLength!=b.flatLength){
        throw std::runtime_error("Tensors not of same volume, cannot elementwise multiply");

    }

    SgNet::Tensor out(this->dims);

    out.data = data.copy();
    out.data *= b.data;

    return out;
}

SgNet::Tensor SgNet::Tensor::operator+ (SgNet::Tensor b){

    // bounds checking
    if(this->flatLength!=b.flatLength){
        throw std::runtime_error("Tensors not of same volume, cannot elementwise multiply");

    }

    SgNet::Tensor out(this->dims);

    out.data = data.copy();
    out.data += b.data;

    return out;
}


void SgNet::Tensor::min(double val){
    data.min(val);
}

SgNet::Vector SgNet::Tensor::shape(){
    return dims;
}

SgNet::Tensor SgNet::Tensor::square() const{
    SgNet::Tensor out(this->dims);

    out.data = data.square();
    return out;
}

SgNet::Tensor SgNet::Tensor::tanh() const{
    SgNet::Tensor out(this->dims);

    out.data = data.tanh();
    return out;
}

SgNet::Tensor SgNet::Tensor::exp() const{
    SgNet::Tensor out(this->dims);

    out.data = data.exp();

    return out;
}

