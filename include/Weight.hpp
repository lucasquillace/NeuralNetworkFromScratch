#ifndef WEIGHT_HPP
#define WEIGHT_HPP

#include <vector>

#define RAND_M 20

/*
 * Class that encapsule a single weight matrix (rappresented as a vector) between 2 layers
*/
class Weight{
    private:
        std::vector<float> layerWeights;
        static int convert_dimention(int, int, int);

    public:
        Weight(int succ_layer_dim, int prec_layer_dim): layerWeights(succ_layer_dim*prec_layer_dim, rand()% RAND_M) {}
};

#endif