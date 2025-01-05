#include "neural/layer/flatten.h"
#include "tensor/tensor.h"

SgNet::Flatten::Flatten(int nOutputDims){
    this->nOutputDims = nOutputDims;
}

SgNet::Tensor SgNet::Flatten::forward(SgNet::Tensor inputs){
    this->inputDims = inputs.dims;

    int smallDimWidth = 1;
    for(int i=nOutputDims-1;i<inputs.dims.size();i++){
        smallDimWidth *= inputs.getDim(i);
    }
    
    SgNet::Vector outDims = inputs.dims.slice(0,nOutputDims-1);
    outDims.append(smallDimWidth);

    SgNet::Tensor out(outDims);

    // no transformations required! We just need to copy the data over, with the new dimensions, since our data is all once dimensional anyway.
    out.copyData(inputs);

    return out;
}

SgNet::Tensor SgNet::Flatten::backward(SgNet::Tensor dValues){
    SgNet::Tensor back(inputDims);
    back.copyData(dValues);

    return back;
}