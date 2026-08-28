#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

#define RAND_M 20

/*
 * Class that encapsule a single matrix (rappresented as a vector) between 2 layers.
 * It has prec_layer x succ_layer dimention. 
 * (So for feed forward, the first layer must be transposted in order to be multiplied with the next weight matrix) 
*/
class Matrix{
    private:
        std::vector<float> matrixValue;
        int row_dim;
        int col_dim;

        static int convert_dimention(int, int, int);

    public:
        Matrix(int succ_layer_dim, int prec_layer_dim): matrixValue(succ_layer_dim*prec_layer_dim, rand()% RAND_M), row_dim(prec_layer_dim) , col_dim(succ_layer_dim) {}

        int getRowDim() const;
        int getColDim() const;
};

#endif