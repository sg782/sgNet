# this is my first cmakeLists file

cmake_minimum_required(VERSION 3.10)

project(sgNet VERSION 1.0.0 LANGUAGES CXX)

add_library(SgNet 
    src/tensor/vector.cpp
    src/tensor/tensor2d.cpp
    src/neural/layer/affine.cpp
    src/neural/layer/relu.cpp
    src/neural/layer/softmax.cpp
    src/utils/frisbee.cpp
    src/neural/loss/categoricalCrossEntropy.cpp
    src/utils/fileReading.cpp
)


target_include_directories(SgNet
PUBLIC 
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_executable(testApp main.cpp)

target_link_libraries(testApp PRIVATE SgNet)

target_compile_features(SgNet PUBLIC cxx_std_17)
target_compile_features(testApp PUBLIC cxx_std_17)