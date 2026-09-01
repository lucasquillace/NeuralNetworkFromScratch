#include <cstdlib>
#include <vector>

#include "Matrix.hpp"

Matrix::Matrix(std::vector<float> values){
    this->matrixValue.reserve(values.size());
    this->col_qtity = values.size();
    this->row_qtity = 1;

    this->matrixValue.assign(values.begin(), values.end());
}

// così da fare la matrice succ_layer_dim x prec_layer_dim
size_t Matrix::convert_dimention(size_t row, size_t col, size_t n_cols){
    return col + (row * n_cols);
}

size_t Matrix::getColQuantity() const{
    return this->col_qtity;
}

size_t Matrix::getRowQuantity() const{
    return this->row_qtity;
}

void Matrix::clear(){
    for (size_t i = 0; i< this->matrixValue.size(); i++){
        this->matrixValue[i] = 0;
    }
}

float Matrix::getValue(size_t index) const{
    return this->matrixValue[index];
}

void Matrix::putValue(size_t index, float value){
    this->matrixValue[index] = value;
}