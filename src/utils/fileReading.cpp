#include "utils/fileReading.h"
#include "tensor/tensor2d.h"
#include "tensor/vector.h"
#include "string.h"
#include <sstream>
#include <fstream>

//Eigen::MatrixXd data, Eigen::Matrix<double, 1, Eigen::Dynamic> labels
void SgNet::loadData2d(
    SgNet::Tensor2d& data,
    SgNet::Vector& labels,
    int maxRows
) {

    //IF YOU ARE EXPERIENCING ISSUES WITH THIS FUNCTION, TRY SWAPPING THE DIMENSIONS FOR labels

    std::string path = "C:/Users/User/Desktop/Machine Learning/datasets/mnist_train.csv";

    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("File could not be found");
    }

    std::vector<std::vector<double>> rawData;
    std::vector<double> rawLabels;
    std::string line;

    // skip first line
    std::getline(file, line);

    int count = 0;


    while (std::getline(file, line)) {


        // for testing
        count++;
        if (count > maxRows) {
            break;
        }


        std::stringstream lineStream(line);
        std::string cell;
        std::vector<double> row;

        // add the label
        std::getline(lineStream, cell, ',');
        rawLabels.push_back(std::stod(cell));


        while (std::getline(lineStream, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        rawData.push_back(row);
    }
    file.close();

    int rows = rawData.size();
    int cols = rawData[0].size();

    SgNet::Tensor2d _data({rows,cols});
    SgNet::Vector _labels(rows);

    for (size_t i = 0; i < rows; i++) {
        _labels[i] = rawLabels[i];
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            _data[i][j]= rawData[i][j];
        }
    }
    

    labels = _labels;
    data = _data;


}


void SgNet::loadMnistData(
    SgNet::Tensor& data,
    SgNet::Vector& labels,
    int maxRows
) {

    //IF YOU ARE EXPERIENCING ISSUES WITH THIS FUNCTION, TRY SWAPPING THE DIMENSIONS FOR labels

    std::string path = "C:/Users/User/Desktop/Machine Learning/datasets/mnist_train.csv";

    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("File could not be found");
    }

    std::vector<std::vector<double>> rawData;
    std::vector<double> rawLabels;
    std::string line;

    // skip first line
    std::getline(file, line);

    int count = 0;


    while (std::getline(file, line)) {


        // for testing
        count++;
        if (count > maxRows) {
            break;
        }


        std::stringstream lineStream(line);
        std::string cell;
        std::vector<double> row;

        // add the label
        std::getline(lineStream, cell, ',');
        rawLabels.push_back(std::stod(cell));


        while (std::getline(lineStream, cell, ',')) {
            row.push_back(std::stod(cell));
        }
        rawData.push_back(row);
    }
    file.close();

    int rows = rawData.size();
    int cols = rawData[0].size();

    SgNet::Tensor2d _data({rows,cols});
    SgNet::Vector _labels(rows);

    for (size_t i = 0; i < rows; i++) {
        _labels[i] = rawLabels[i];
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            _data[i][j]= rawData[i][j];
        }
    }
    

    labels = _labels;
    data.copyData(_data);
}




    