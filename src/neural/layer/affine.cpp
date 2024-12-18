#include "neural/layer/affine.h"
#include <vector>


// due to the existence of the Generic type, we must do somethign special here
// should i look into inheritance for the tensors (yes);


template <typename T>
SgNet::Affine<T>::Affine(int nDims, std::vector<int> dims){
    b.resize(dims[0]);
    w = T();
}

template <typename T>
T SgNet::Affine<T>::forward(T inputs){
    return inputs * 2;
}

template <typename T>
T SgNet::Affine<T>::backward(T dValues){
    return dValues;
}
    