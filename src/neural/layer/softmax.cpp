#include "neural/layer/softmax.h"

// for if th
SgNet::Softmax::Softmax(int nInputs){

}

SgNet::Tensor2d SgNet::Softmax::forward(SgNet::Tensor2d inputs){

    // subtract max of each row, as it does not affect the output but improves stability 

    SgNet::Tensor2d out(inputs.shape());
    for(int i=0;i<out.numRows();i++){
        out[i] = inputs[i].exp();
        double rowSum = out[i].sum();
        out[i] /= rowSum;
    }
    output = out;
    return out;
}

SgNet::Tensor2d SgNet::Softmax::backward(SgNet::Tensor2d dValues){

	// https://eli.thegreenplace.net/2016/the-softmax-function-and-its-derivative/
    SgNet::Tensor2d out(dValues.shape());

    // we can optimize later, my other code has a vectorized version
    for(int i=0;i<dValues.numRows();i++){
        double sum = output[i].dot(dValues[i]);

        out[i] = output[i] * (dValues[i] - sum);

    }

    return out;
}