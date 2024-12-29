#include "neural/layer/softmax.h"

// for if th
SgNet::Softmax::Softmax(int nInputs){

}

SgNet::Tensor SgNet::Softmax::forward(SgNet::Tensor inputs, int axis){

    this->axis = axis;
    this->inputs = inputs;
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
        Tensor section = inputs.tensorAt(idx);
        double maxVal = section.data.max();
        SgNet::Tensor expVals = (section-maxVal).exp();

        SgNet::Tensor subOut = expVals/expVals.sum();

        out.tensorAt(idx).copyData(subOut);
    }

    this->output = out;
    return out;
}


void other(){
//     Eigen::MatrixXd gradients(dValues.rows(), dValues.cols());
//     for (int i = 0; i < dValues.rows(); i++) {
//         Eigen::VectorXd upStreamVector = dValues.row(i);


//         double sum = output.row(i).dot(upStreamVector);


//         Eigen::Matrix<double, 1, Eigen::Dynamic> gradient = output.row(i).array().transpose() * (upStreamVector.array() - sum);

//         gradients.row(i) = gradient;
//     }




    // for(int i=0;i<dValues.numRows();i++){
    //     double sum = output[i].dot(dValues[i]);
    //     out[i] = output[i] * (dValues[i] - sum);
    // }
 }

// SgNet::Tensor SgNet::Softmax::backward(SgNet::Tensor dValues){

// 	// https://eli.thegreenplace.net/2016/the-softmax-function-and-its-derivative/
//     SgNet::Tensor dOut(dValues.dims);
//     SgNet::Vector kernelDims = inputs.dims.slice(0,inputs.dims.size()-axis);

//     SgNet::Vector idx(axis);

    

//     // we can optimize later, my other code has a vectorized version
//     for(int i=0;i<dValues.flatLength;i+=kernelDims.product()){

//         idx = inputs.getDimensionalIndex(i).slice(0,axis);

//         double sum = (output.tensorAt(idx) * dValues.tensorAt(idx)).sum();



//         dOut.tensorAt(idx).copyData(output.tensorAt(idx) * (dValues.tensorAt(idx) - sum));
//     }

//     std::cout << "Softmax:\n";
//     inputs.print();
//     dValues.print();
//     dOut.print();
//     std::cout << "-------\n";

//     return dOut;
// }



SgNet::Tensor SgNet::Softmax::backward(SgNet::Tensor dValues){

	// https://eli.thegreenplace.net/2016/the-softmax-function-and-its-derivative/
    SgNet::Tensor dOut(dValues.dims);
    SgNet::Vector kernelDims = inputs.dims.slice(0,inputs.dims.size()-axis);
    SgNet::Vector idx(axis);

    // we can optimize later, my other code has a vectorized version
    for(int i=0;i<dValues.flatLength;i+=kernelDims.product()){

        idx = inputs.getDimensionalIndex(i).slice(0,axis);

        double sum = (output.tensorAt(idx) * dValues.tensorAt(idx)).sum();
        dOut.tensorAt(idx).copyData(output.tensorAt(idx) * (dValues.tensorAt(idx) - sum));
    }


    return dOut;
}