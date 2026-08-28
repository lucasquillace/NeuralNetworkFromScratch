#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <memory>

class Layer;
class Weight;
/*
 * Class that encapsule all the network
*/
class Network{
    private:
        std::vector<std::unique_ptr<Layer>> layers;
        std::vector<std::unique_ptr<Weight>> weights;

        float activation_function(float) const;

    public:
        Network();
        
        // per specificare il numero di layer, compreso quello di input ed i nodi necessari per layer
        Network(int, std::vector<int>);

        // feed forward pass
        void feed_forward();
        
        // return the value of the loss funcion
        float cost();
};

#endif