#pragma once

#ifndef CONVOLUTION_2D_H
#define CONVOLUTION_2D_H

#include "tensor/tensor.h"
#include "tensor/vector.h"
#include <array>

namespace SgNet{

	class Convolution2d {
	public:
		std::array<int, 2> kernelShape;
		int inputChannels;
		int numFilters;
		int strideLength;
		int padding;
		double learningRate;



		Tensor filters;
		Vector bias;

		Tensor inputs;
		Tensor paddedInputs;

		/*
		std::vector<std::vector<Eigen::MatrixXd>> inputs
		batch , filters, input+
		*/

		Convolution2d() = default;
		Convolution2d( std::array<int,2> kernelShape, int inputChannels, int numFilters, double learningRate, int strideLength, int padding);


		Tensor forward(Tensor inputs);


		Tensor backward(Tensor dValues);
	};

}



#endif