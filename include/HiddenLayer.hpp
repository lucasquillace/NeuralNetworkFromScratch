#ifndef HIDDEN_LAYER_HPP
#define HIDDEN_LAYER_HPP

#include <vector>
#include "Layer.hpp"

class HiddenLayer : public Layer{

    public:
        using Layer::Layer;
        HiddenLayer(int nodes_number): Layer(nodes_number) {}

        void update_node_values(std::vector<float>) override;

};

#endif