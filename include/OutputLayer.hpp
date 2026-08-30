#ifndef OUTPUT_LAYER_HPP
#define OUTPUT_LAYER_HPP

#include <vector>
#include "Layer.hpp"

/*
 * 47 Nodes
*/
class OutputLayer : public Layer{

    private:
        std::vector<std::vector<float>> expected_values;

    public:
        using Layer::Layer;
        OutputLayer(int nodes_number): Layer(nodes_number) {}

        void update_node_values(std::vector<float>) override;

        //obv the expected outcome will be 1 on the float(th) node and 0 otherwise
        void push_expected_value(float);
};

#endif