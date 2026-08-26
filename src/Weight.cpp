#include <cstdlib>
#include <vector>

#include "Weight.hpp"


// così da fare la matrice succ_layer_dim x prec_layer_dim
int Weight::convert_dimention(int row, int col, int n_cols){
    return col + (row * n_cols);
}
