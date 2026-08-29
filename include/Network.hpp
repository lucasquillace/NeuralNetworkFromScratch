#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <memory>

class Layer;
class Matrix;
/*
 * Class that encapsule all the network
*/
class Network{
    private:
        std::vector<std::unique_ptr<Layer>> layers;

        // weights[i] is the weight matrix between (i-1) and (i) layer
        std::vector<std::unique_ptr<Matrix>> weights;

        float activation_function(float) const;

    public:
        Network();
        
        // per specificare il numero di layer, compreso quello di input ed i nodi necessari per layer
        Network(int, std::vector<int>);

        // (maybe there's a better design choice but i don't want to create a shared_ptr)
        std::unique_ptr<Matrix>* getWeights(int);
        
        // return the value of the loss funcion
        float cost();

        // feed forward pass
        void feed_forward();
};

#endif