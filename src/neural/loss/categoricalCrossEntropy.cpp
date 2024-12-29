#include "neural/loss/categoricalCrossEntropy.h"
#include "tensor/tensor2d.h"
#include <cmath>
#include <stdexcept>


SgNet::CCE::CCE(){

}

double SgNet::CCE::calculate(SgNet::Tensor x, SgNet::Vector y){
    // assume Tensor input is 2d
    if(x.nDims != 2){
        throw std::invalid_argument("Categorical Cross entropy requires a Tensor of dimension 2");
    }


    // we will average across the whole batch
    double loss = 0.0;
    SgNet::Vector idx(2);


    for(int i=0;i<x.getDim(0);i++){
        int correctClassIdx = y[i].val();
        idx = std::vector<int>{i,correctClassIdx};
        loss +=  -1 * std::log(x.at(idx).val());
    }

    loss /= x.getDim(0);

    return loss;
}

SgNet::Tensor SgNet::CCE::backward(SgNet::Tensor yPred, SgNet::Vector y){
    if(yPred.nDims != 2){
        throw std::invalid_argument("Categorical Cross entropy requires a Tensor of dimension 2");
    }
    SgNet::Tensor out(yPred.dims);
    out.setConstant(0);

    double epsilon = 1e-10;

    SgNet::Vector idx(2);

    for(int i=0;i<yPred.getDim(0);i++){
        int correctClassIdx = y[i].val();
        idx = std::vector<int>{i,correctClassIdx};

        out.at(idx) = -1 / (yPred.at(idx).val() + epsilon);
    }

    out.print();
    y.print();

    return out;
}