#include "convolution2d.h"
#include <array>
#include <algorithm>
#include "tensor/tensor.h"
#include "tensor/vector.h"
#include <iostream>


/*
	NOT at all optimized. Incorporating stride into this has caused some initial struggle. 
	I have spent the last few hours on a bus ride devoting about 60% of my attention to deriving
	the convolutional backpropagation by hand, lets find out if it works. (12/12/24)
*/

SgNet::Convolution2d::Convolution2d(std::array<int, 2> kernelShape, int inputChannels, int numFilters, double learningRate, int strideLength, int padding) {
	this->kernelShape = kernelShape;
	this->inputChannels = inputChannels;
	this->numFilters = numFilters;
	this->strideLength = strideLength;
	this->padding = padding;
	this->learningRate = learningRate;


	// initialize weights and biases
	this->filters = Tensor(std::vector<int>{numFilters,kernelShape[0],kernelShape[1]});

	for (int i = 0; i < numFilters; i++) {
		filters[i].setRandomGaussian(0,1);
		filters[i] *= std::sqrt(2. / kernelShape[0]);
	}
	this->bias = SgNet::Vector(numFilters);
    this->bias.setConstant(0);
}

SgNet::Tensor SgNet::Convolution2d::forward(SgNet::Tensor inputs) {

	/*
	input -> (batchSize , inputChannels, [data])
	output -> (batchSize, numFilters, [data])
	*/
	this->inputs = inputs;

	int n = inputs.dims[0].val();
	
	// assume all layers have the same depth
	int numChannels = inputs.dims[1].val();
	int inputRows = inputs.dims[2].val();
	int inputCols = inputs.dims[3].val();

    
    Tensor paddedInputs(std::vector<int>{n,numChannels,inputRows + 2*padding,inputCols + 2*padding});
	//Eigen::MatrixXd paddedInput(inputRows + 2 * padding, inputCols + 2 * padding);
	//paddedInput.setZero();

	// pad inputs for each channel of each input
    Vector startPoint(4);

    // i need to improve vector initialization
    startPoint[0] = 0;
    startPoint[1] = 1;
    startPoint[2] = padding;
    startPoint[3] = padding;



    paddedInputs.block(startPoint,inputs.dims) = inputs;
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < numChannels; j++) {
	// 		paddedInputs[i][j].block(padding, padding, inputRows, inputCols) = inputs[i][j];
	// 	}
	// }
	this->paddedInputs = paddedInputs;


	int outputRows = ((inputRows + 2 * padding - kernelShape[0]) / strideLength) + 1;
	int outputCols = ((inputCols + 2 * padding - kernelShape[1]) / strideLength) + 1;

	
	std::vector<std::vector<Eigen::MatrixXd>> output(n,
		std::vector<Eigen::MatrixXd>(numFilters,Eigen::MatrixXd::Zero(outputRows, outputCols))
	);


	for (int i = 0; i < n; i++) {
	// for each test in batch

		for (int j = 0; j < numFilters; j++) {
		// for ecah output filter

			for (int p = 0; p < inputChannels; p++) {
			// run the convolution, sum across all input channels

				// we will assume there are no bounding issues
				for (int k = 0; k < outputRows; k++) {
					for (int l = 0; l < outputCols; l++) {

						// summation across all n batches

						output[i][j](k, l) += (paddedInputs[i][p].block(k * strideLength, l * strideLength, filters[j].rows(), filters[j].cols()).array() * filters[j].array()).sum();


						// we will assume bounding is correct
						// --- int boundedLeft = std::max(k-(kernelShape[0] / 2) + 1, 0);
						// --- int boundedRight = std::max(k+)

						//Eigen::MatrixXd area = input.block()
					}
				}
			}


			// add bias of filter j to the output activation
			output[i][j].array() += bias(j);
		}
	}

	
	return output;


	/*
		output =  ((inputDim + 2*padding - kernelWidth) / strideLength) + 1
	*/
}

std::vector<std::vector<Eigen::MatrixXd>> Convolution2d::backward(std::vector<std::vector<Eigen::MatrixXd>> dValues) {

	int batchSize = dValues.size();
	

	/*
		Must calculate dW,dB, and dInputs **for each channel**

		**we will also average across our batch**
	*/
	// dB
	Eigen::VectorXd db(numFilters);
	db.setZero();

	for (int i = 0; i < batchSize; i++) {
		for (int j = 0; j < numFilters; j++) {
			// sum db across all items in the batch
			db(j) += dValues[i][j].sum();
		}
	}
	db /= batchSize;
	

	// dW
	std::vector<Eigen::MatrixXd> dW(numFilters, Eigen::MatrixXd(filters[0].rows(),filters[0].cols()));
	for (int i = 0; i < dW.size(); i++) {
		dW[i].setZero();
	}
	for (int i = 0; i < batchSize; i++) {
		for (int j = 0; j < numFilters; j++) {
			// since we are zero indexed, the formula will be slightly altered
			
			for (int k = 0; k < filters[j].rows(); k++) {
				for (int l = 0; l < filters[j].cols(); l++) {

					for (int m = 0; m < dValues[i][j].rows(); m++) {
						for (int n =  0; n < dValues[i][j].cols(); n++) {
							int dValRow = (m * strideLength) + k;
							int dValCol = (n * strideLength) + l;

							// sum all
							dW[j](k, l) += paddedInputs[i][j](dValRow, dValCol) * dValues[i][j](m,n);
						}
					}

				}
			}
			// due to the existence of stride, we cannot just take a cut out of the original matrix
		}
	}
	
	// average across batch
	for (int i = 0; i < dW.size(); i++) {
		dW[i] /= batchSize;
	}
	
	// dInputs
	//how each value affects the output -> loss

	/*
	To calculate dL/dInputs:
	We are calculate the derivative of the output with respect to the inputs.

	we are trying to find by how much each input value affects the output

	the relationship between the inputs and the outputs is through the convolution, more specifically, 
	through each multiplication of one input vlaue with one kernel value
	
	
	
	
	*/



	// fully naive and shameless 'solution'
	std::vector<std::vector<Eigen::MatrixXd>> dInputs(batchSize, std::vector<Eigen::MatrixXd>(numFilters,Eigen::MatrixXd(inputs[0][0].rows(),inputs[0][0].cols())));

	for (int i = 0; i < batchSize; i++) {
		for (int j = 0; j < numFilters; j++) {

			// this part especially can be trimmed down
			for (int k = 0; k < inputs[i][j].rows();k++) {
				for (int l = 0; l < inputs[i][j].cols();l++) {

					for (int m = 0; m < dValues[i][j].rows(); m++) {
						for (int n = 0; n < dValues[i][j].cols(); n++) {

							// inside this loop we can quite explicitly find dO[m,n] / dA[k,l]
							int weightIndexRow = k - (m * strideLength);
							int weightIndexCol = l - (n * strideLength);

							// i said shameless
							// here, we are checking if our weight indices are in  bounds
							if (weightIndexRow >= 0 && 
								weightIndexCol >= 0 &&
								weightIndexRow < filters[j].rows() && 
								weightIndexCol < filters[j].cols()
								) {

								dInputs[i][j](k,l) += filters[j](weightIndexRow, weightIndexCol) * dValues[i][j](m,n);
							}
							else {
								// add zero
							}

						}
					}
				}
			}


		}
	}
	
	//update weights (in theory)


	// might need to call .array()
	bias -= db * learningRate;

	for (int i = 0; i < numFilters; i++) {
		filters[i].array() -= dW[i].array() * learningRate;
	}



	/*
		in theory, that is the backpropagation fully implemented. It is most definitely not correct. We can dream.

	
	*/



	

	return dInputs;
}
