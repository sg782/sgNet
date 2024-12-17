#include "tensor/tensorNd.h"
#include <iostream>
#include <vector>




SgNet::Tensor::Tensor(int nDimensions, std::vector<int> dimensions){
    std::cout << nDimensions << "\n";
    this -> nDimensions = nDimensions;
    this->dimensions = dimensions;
    flatLength = 1;
    for(int i=0;i<nDimensions;i++){
        flatLength*=dimensions[i];
    }

    // initialize to zero
    flatVector = std::vector<double>(flatLength);
    for(int i=0;i<flatLength;i++){
        flatVector[i] = 0;
    }

};

void SgNet::Tensor::test(){
    std::cout << "test works";
}

void SgNet::Tensor::print(){
    std::vector<int> printDims = std::vector<int>(nDimensions);
    

    printDims[nDimensions - 1] = dimensions[nDimensions -1];
    for(int i=nDimensions-2;i>=0;i--){
        printDims[i] = printDims[i+1] * dimensions[i];
    }


    for(int i=0;i<flatLength;i++){
        for(int j=0;j<printDims.size();j++){
            if(i % printDims[j] == 0){
                std::cout << "\n";
            }
        }
        std::cout << flatVector[i] << " ";

    }
}