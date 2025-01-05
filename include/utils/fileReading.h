#pragma once
#ifndef FILEREADING_H
#define FILEREADING_H

#include "tensor/tensor2d.h"
#include "tensor/vector.h"
#include "tensor/tensor.h"

namespace SgNet {
    void loadData2d(Tensor2d& data, Vector& labels, int maxRows);

    void loadMnistData(Tensor& data, Vector& labels, int maxRows);

    void loadMnistConvData(Tensor&data, Vector&labels, int maxRows);
};



#endif
