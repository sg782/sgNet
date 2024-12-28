#include "neural/layer/softmax.h"

// for if th
SgNet::Softmax::Softmax(int nInputs){

}

SgNet::Tensor SgNet::Softmax::forward(SgNet::Tensor inputs, int axis){
    // does the softmax function over a specific set of dimensions

    // subtract max of each row, as it does not affect the output but improves stability 

    // dimension of relevant softmax kernel shape (since it may not be 2d)
    // kernel may not be the appropriate term
    SgNet::Vector kernelDims = inputs.dims.slice(0,inputs.dims.size()-axis);

    SgNet::Tensor out(inputs.dims);

    int numKernels = inputs.flatLength/kernelDims.product();
    
    SgNet::Vector idx(axis);
    for(int i=0;i<inputs.flatLength;i+=kernelDims.product()){
        idx = inputs.getDimensionalIndex(i).slice(0,axis);
        SgNet::Tensor expVals = inputs.tensorAt(idx).exp();
        SgNet::Tensor subOut = expVals/expVals.sum();

        subOut.print();

        Vector append(inputs.nDims-kernelDims.size());
        append = 1;
        Vector appendedDims = append.concat(kernelDims);


        // i need to really fix data transfer methods
        // this is the only one i could get to work
        out.block(inputs.getDimensionalIndex(i),appendedDims).data.setValues(subOut.data);

    }

    // for(int i=0;i<out.numRows();i++){
    //     out[i] = inputs[i].exp();
    //     double rowSum = out[i].sum();
    //     out[i] /= rowSum;
    // }
    // output = out;
    // return out;
    return out;
}

// SgNet::Tensor SgNet::Softmax::backward(SgNet::Tensor dValues){

// 	// https://eli.thegreenplace.net/2016/the-softmax-function-and-its-derivative/
//     SgNet::Tensor out(dValues.shape());

//     // we can optimize later, my other code has a vectorized version
//     for(int i=0;i<dValues.numRows();i++){
//         double sum = output[i].dot(dValues[i]);

//         out[i] = output[i] * (dValues[i] - sum);

//     }

//     return out;
// }