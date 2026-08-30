#ifndef OUTPUT_LAYER_HPP
#define OUTPUT_LAYER_HPP

#include <vector>
#include "Layer.hpp"

/*
 * 47 Nodes
 * I use the index of InputLayer (*local_index_ptr) to maintain the same index in cached values
*/
class OutputLayer : public Layer{

    private:
        std::vector<std::vector<float>> expected_values;

        // this pointer holds the value of the index in InputLayer's cache
        uint8_t* local_index_ptr;
        
    public:
        using Layer::Layer;
        OutputLayer(int nodes_number): Layer(nodes_number) {}

        void update_node_values(std::vector<float>) override;

        // functions to synch vales with the Input Layer
        //obv the expected outcome will be 1 on the float(th) node and 0 otherwise
        void synch_expected_values(std::vector<float>&&);
        void synch_index(uint8_t*);

        void clear_cached_values();

        float getNodeValueByPosition(int) const;
        float getExpectedNodeValueByPosition(int) const;

};

#endif