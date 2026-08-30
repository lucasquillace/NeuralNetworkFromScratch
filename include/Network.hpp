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

        float loss_function(float, float) const;

    public:
        Network();
        
        // per specificare il numero di layer, compreso quello di input ed i nodi necessari per layer
        Network(int, std::vector<int>);

        // calculate the loss between the predicted values of the network and the expected ones
        float cost();

        // feed forward pass
        void feed_forward();
};

#endif