#include <cstdlib>
#include <vector>

#include "Matrix.hpp"


// così da fare la matrice succ_layer_dim x prec_layer_dim
int Matrix::convert_dimention(int row, int col, int n_cols){
    return col + (row * n_cols);
}

int Matrix::getColDim() const{
    return this->col_dim;
}

int Matrix::getRowDim() const{
    return this->row_dim;
}