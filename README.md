# SgNet
Basic neural network framework for learning purposes. 


### Project Notes

My motivation for this project was sourced from my struggle to link a pre-existing NN library. It is also much more fun to create something from scratch than to just download one that works better.

I primarily developed this over the course of a month or so between semesters, with my goal being to implement the **logic** behind Neural Networks.

Performance was **NOT** my goal here, neither was clean code.


### Future

This project is currently heavily unoptimized. In the future I plan to write dedicated GPU kernels to improve performance, with the end goal being to release this as a complete library. 

I also plan to extend supported datatypes for all vectors and tensors to any generic type


# Docs 
## Neural

## Tensor
This project initially used [*Eigen*](https://eigen.tuxfamily.org/dox/), a linear algebra library. Unfortunately (per my knowledge) Eigen only has support for two-dimensional matrices, which became a bottleneck in more complex networks. 

To combat this issue, I developed an N-dimensional tensor class, along with a few other supplementary classes. These classes are defined below.

#### tensor.h


#### tensor2d.h

#### vector.h


https://www.markdownguide.org/cheat-sheet/


*** look into doxygen