#include "neural/loss/categoricalCrossEntropy.h"
#include "tensor/tensor2d.h"
#include <cmath>


SgNet::CCE::CCE(){

}

double SgNet::CCE::calculate(SgNet::Tensor2d x, SgNet::Vector y){
    // we will average across the whole batch
    double loss = 0.0;

    for(int i=0;i<x.numRows();i++){
        int correctClassIdx = y[i].val();
        loss +=  -1 * std::log(x[i][correctClassIdx].val());
    }

    loss /= x.numRows();

    return loss;
}

SgNet::Tensor2d SgNet::CCE::backward(SgNet::Tensor2d yPred, SgNet::Vector y){
    SgNet::Tensor2d out(yPred.shape());
    out.setConstant(0);

    	double epsilon = 1e-10;


    for(int i=0;i<yPred.numRows();i++){
        out[i][y[i].val()] = -1 / (yPred[i][y[i].val()].val() + epsilon);
    }

    return out;
}