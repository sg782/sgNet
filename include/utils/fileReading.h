#pragma once
#ifndef FILEREADING_H
#define FILEREADING_H

#include "tensor/tensor2d.h"
#include "tensor/vector.h"

namespace SgNet {
    void loadData(Tensor2d& data, Vector& labels, int maxRows);
};



#endif
