#include "neural/layer/affine_t.h"
#include <vector>
#include <iostream>
#include "utils/timer.h"
#include <cmath>

// due to the existence of the Generic type, we must do somethign special here
// should i look into inheritance for the tensors (yes);


SgNet::Affine_t::Affine_t(int nDims, std::vector<int> dims,double learningRate){

    /*
    Affine layer: Takes an arbitrarily dimensional Tensor, and performs an affine transformation on its 2 innermost dimensions
    */

    this->learningRate = learningRate;




    

    // initialize weight tensor
    w = SgNet::Tensor({dims[nDims-2],dims[nDims-1]});
    w.setRandomGaussian(0,1);
    w *= std::sqrt(2. / dims[0]);

    
    b.setConstant(0.0);


}

SgNet::Tensor SgNet::Affine_t::forward(SgNet::Tensor inputs){
    this-> inputs = inputs;

    // forward pass on generic tensor type


    // in = {3,4,5,5} -> out = {3,4,5,3}

    // format the output dimension
    SgNet::Vector outputDims = inputs.dims.copy();
    outputDims[outputDims.size()-1] = w.getDim(1);
    SgNet::Tensor out({outputDims});

    // for indexing over the flat data
    int jumpLength = w.dims.product();


    // explicitly traverse over the nDims-2 outermost dimensions (all but the innermost two)
    for(int i=0;i<out.flatLength;i+=jumpLength){
        SgNet::Vector indices = out.getDimensionalIndex(i).slice(0,out.nDims-2);

        // inputs.tensorAt(indices).print();
        // inputs.tensorAt(indices).matMult(w).print();

        // Tensor d = inputs.tensorAt(indices);
        // Tensor output = d.matMult(w);

        // inputs.tensorAt(indices).matMult(w);

        out.tensorAt(indices).copyData(inputs.tensorAt(indices).matMult(w));

    }


    //out.byRow() += b;



    return out;
}

// SgNet::Tensor2d SgNet::Affine_t::backward(Tensor2d dValues){



//     Tensor2d dW = inputs.transpose().matMult(dValues);
//     Vector dB = dValues.colSum();



//     Tensor2d dInputs = dValues.matMult(w.transpose());



//     // update weights
//     w -= (dW * learningRate);
//     b -= (dB * learningRate);

//     return dInputs;
// }