#ifndef OUTPUT_LAYER_HPP
#define OUTPUT_LAYER_HPP

#include <vector>
#include "Layer.hpp"


class OutputLayer : public Layer{

    public:
        using Layer::Layer;
        OutputLayer(int nodes_number): Layer(nodes_number) {}

        void update_node_values(std::vector<float>) override;

};

#endif