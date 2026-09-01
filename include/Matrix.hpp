#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

#define RAND_M 20

/*
 * Class that encapsule a single matrix (rappresented as a vector) between 2 layers.
 * It has prec_layer (quantity of rows, "vertical component") x succ_layer dimention (quantity of cols, "orizontal component"). 
 * (So for feed forward, the first layer must be transposted in order to be multiplied with the next weight matrix) 
*/
class Matrix{
    private:
        std::vector<float> matrixValue;
        size_t row_qtity;
        size_t col_qtity;


    public:
        Matrix(size_t succ_layer_dim, size_t prec_layer_dim): matrixValue(succ_layer_dim*prec_layer_dim, rand()% RAND_M), row_qtity(prec_layer_dim) , col_qtity(succ_layer_dim) {}
        
        // initialize an array of dimention 1 on the fly
        Matrix(std::vector<float> values);

        // returns the quantity of rows and cols
        size_t getRowQuantity() const;
        size_t getColQuantity() const;

        // get or put a value on the matrixValue vector
        float getValue(size_t) const;
        void putValue(size_t, float);

        // empties the matrix. Gurantees no reallocation
        void clear();

        // converts from 2d coordinates to array coordinates. 
        static size_t convert_dimention(size_t row_number, size_t col_number, size_t col_quantity);


};

#endif