#ifndef INPUT_LAYER_HPP
#define INPUT_LAYER_HPP

#include <vector>

#include "Layer.hpp"

class InputLayer : public Layer{

    public:
        using Layer::Layer;
        InputLayer(int nodes_number): Layer(nodes_number) {}
        
        void update_node_values(std::vector<float> ) override;

};

#endif