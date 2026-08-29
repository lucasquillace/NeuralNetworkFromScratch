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
int Matrix::convert_dimention(int row, int col, int n_cols){
    return col + (row * n_cols);
}

int Matrix::getColQuantity() const{
    return this->col_qtity;
}

int Matrix::getRowQuantity() const{
    return this->row_qtity;
}

void Matrix::clear(){
    for (int i = 0; i< this->matrixValue.size(); i++){
        this->matrixValue[i] = 0;
    }
}

float Matrix::getValue(int index) const{
    return this->matrixValue[index];
}

void Matrix::putValue(int index, float value){
    this->matrixValue[index] = value;
}