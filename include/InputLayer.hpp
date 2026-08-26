#ifndef INPUT_LAYER_HPP
#define INPUT_LAYER_HPP

#include <vector>

#include "Layer.hpp"

class InputLayer : public Layer{

    public:
        using Layer::Layer;
        InputLayer(int nodes_number): Layer(nodes_number) {}

        std::vector<float> find_node_values() override;
};

#endif