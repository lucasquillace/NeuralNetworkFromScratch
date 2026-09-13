#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <memory>

class Layer;
class Matrix;
/*
 * Class that encapsule all the network. 
 * In the backprop() the function maeks a strong assumption: 
 * THE NETWORK IS USING SIGMOID + BCE, otherwise the function itself doesn't work properly
*/
class Network{
    private:
        std::vector<std::unique_ptr<Layer>> layers;

        // weights[i] is the weight matrix between (i-1) and (i) layer
        std::vector<std::unique_ptr<Matrix>> weights;

        float loss_function(float, float) const;

    public:
        // per specificare il numero di layer, compreso quello di input ed i nodi necessari per layer
        Network(size_t, std::vector<size_t>);

        // calculate the loss between the predicted values of the network and the expected ones
        float cost();

        // feed forward pass
        void feed_forward();

        // backprop pass
        void backprop();
};

#endif