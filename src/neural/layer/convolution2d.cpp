#include <array>
#include <algorithm>
#include "tensor/tensor.h"
#include "tensor/vector.h"
#include <iostream>
#include "neural/layer/convolution2d.h"
#include <cmath>



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
	this->filters = SgNet::Tensor(std::vector<int>{numFilters,kernelShape[0],kernelShape[1]});

	filters.setRandomGaussian(0,1);
	filters*= 2. / kernelShape[0];

    this->bias.resize(numFilters);
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


    
    SgNet::Tensor paddedInputs(std::vector<int>{n,numChannels,inputRows + 2*padding,inputCols + 2*padding});
    paddedInputs.setConstant(0);
	//Eigen::MatrixXd paddedInput(inputRows + 2 * padding, inputCols + 2 * padding);
	//paddedInput.setZero();

	// pad inputs for each channel of each input
    SgNet::Vector startPoint(4);
    startPoint = std::vector<int>{0,0,padding,padding};


    paddedInputs.block(startPoint,inputs.dims).copyData(inputs);

	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < numChannels; j++) {
	// 		paddedInputs[i][j].block(padding, padding, inputRows, inputCols) = inputs[i][j];
	// 	}
	// }
	this->paddedInputs = paddedInputs;


	int outputRows = ((inputRows + 2 * padding - kernelShape[0]) / strideLength) + 1;
	int outputCols = ((inputCols + 2 * padding - kernelShape[1]) / strideLength) + 1;

	// std::vector<std::vector<Eigen::MatrixXd>> output(n,
	// 	std::vector<Eigen::MatrixXd>(numFilters,Eigen::MatrixXd::Zero(outputRows, outputCols))
	// );

    SgNet::Tensor output({n,numFilters,outputRows,outputCols});
	output.setConstant(0);
    
    SgNet::Vector indices(4);
    indices.setConstant(0);

    SgNet::Vector blockIndices(4);

    SgNet::Vector blockDims(4);
    blockDims = std::vector<int>{1,1,kernelShape[0],kernelShape[1]};



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

                        indices = std::vector<int>{i,j,k,l};
                        blockIndices = std::vector<int>{i,j,k*strideLength,l*strideLength};


            
                        

                        SgNet::Tensor block = paddedInputs.block(blockIndices,blockDims);

                        // we can just do the dot prod! since they are represented by flat vectors


                        double convSum = block.data.dot(filters.getAxis(0,j).asVector());



					// 	block.data.print();
					// 	filters.data.print();

                    //    // paddedInputs[i][p].block(k * strideLength, l * strideLength, filters[j].rows(), filters[j].cols())
					// 	std::cout << convSum << "\n";

                        output.at(indices) += convSum;


						// we will assume bounding is correct
						// --- int boundedLeft = std::max(k-(kernelShape[0] / 2) + 1, 0);
						// --- int boundedRight = std::max(k+)

						//Eigen::MatrixXd area = input.block()
					}
				}
			}

			// add bias of filter j to the output activation
            SgNet::Vector ijInd(2);

            ijInd = std::vector<int>{i,j};

			output[i][j].data += bias[j].val();

		}
	}	
	return output;


	/*
		output =  ((inputDim + 2*padding - kernelWidth) / strideLength) + 1
	*/
}

SgNet::Tensor SgNet::Convolution2d::backward(SgNet::Tensor dValues) {

	int batchSize = dValues.getDim(0);
	
	std::cout << "this\n";
	/*
		Must calculate dW,dB, and dInputs **for each channel**

		**we will also average across our batch**
	*/
	// dB
	SgNet::Vector db(numFilters);
	db.setConstant(0);

	for (int i = 0; i < batchSize; i++) {
		for (int j = 0; j < numFilters; j++) {
			// sum db across all items in the batch
			db[j] += dValues[i][j].sum();
		}
	}
	db /= batchSize;
	
	std::cout << "this\n";
	// dW
    SgNet::Tensor dW(std::vector<int>{numFilters,kernelShape[0],kernelShape[1]});
	dW.setConstant(0);

	for (int i = 0; i < batchSize; i++) {
		for (int j = 0; j < numFilters; j++) {
			// since we are zero indexed, the formula will be slightly altered
			
			for (int k = 0; k < kernelShape[0]; k++) {
				for (int l = 0; l < kernelShape[1]; l++) {

                    // could that also be written as dValues.getDim(2) and getDim(3)?
					for (int m = 0; m < dValues.getDim(2); m++) {
						for (int n =  0; n < dValues.getDim(3); n++) {
							int dValRow = (m * strideLength) + k;
							int dValCol = (n * strideLength) + l;

							// sum all
                            dW.at(std::vector<int>{j,k,l}) += paddedInputs.at(std::vector<int>{i,j,dValRow,dValCol}).val() * dValues.at(std::vector<int>{i,j,m,n}).val();
						}
					}

				}
			}
			// due to the existence of stride, we cannot just take a cut out of the original matrix
		}
	}
	
	// average across batch
	dW/=batchSize;

	// dInputs
	//how each value affects the output -> loss

	/*
	To calculate dL/dInputs:
	We are calculate the derivative of the output with respect to the inputs.

	we are trying to find by how much each input value affects the output

	the relationship between the inputs and the outputs is through the convolution, more specifically, 
	through each multiplication of one input vlaue with one kernel value
	
	
	
	
	*/

	std::cout << "this\n";

	// fully naive and shameless 'solution'
    SgNet::Tensor dInputs(inputs.dims);

	for (int i = 0; i < batchSize; i++) {
		for (int j = 0; j < numFilters; j++) {

			// this part especially can be trimmed down
			for (int k = 0; k < inputs[i][j].getDim(0);k++) {
				for (int l = 0; l < inputs[i][j].getDim(1);l++) {

					for (int m = 0; m < dValues.getDim(2); m++) {
						for (int n = 0; n < dValues.getDim(3); n++) {

							// inside this loop we can quite explicitly find dO[m,n] / dA[k,l]
							int weightIndexRow = k - (m * strideLength);
							int weightIndexCol = l - (n * strideLength);

							// i said shameless
							// here, we are checking if our weight indices are in  bounds
							if (weightIndexRow >= 0 && 
								weightIndexCol >= 0 &&
								weightIndexRow < filters[j].getDim(0) && 
								weightIndexCol < filters[j].getDim(1)
								) {

                                dInputs.at(std::vector<int>{i,j,k,l}) += filters.at(std::vector<int>{j,weightIndexRow,weightIndexCol}).val() * dValues.at(std::vector<int>{i,j,m,n}).val();
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
	bias -= (db * learningRate);

    filters -= (dW * learningRate);

    


	/*
		in theory, that is the backpropagation fully implemented. It is most definitely not correct. We can dream.

	
	*/



	

	return dInputs;
    // thats all folks!
}

