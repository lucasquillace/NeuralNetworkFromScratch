#ifndef OUTPUT_LAYER_HPP
#define OUTPUT_LAYER_HPP

#include <vector>
#include "Layer.hpp"
#include "PreActivationValueCache.hpp"

/*
 * I use the index of InputLayer (*local_index_ptr) to maintain the same index in cached values
 * The last layer has 47 nodes
*/
class OutputLayer : public Layer, public PreActivationValueCache{

    private:
        std::vector<std::vector<float>> expected_values;

        // this pointer holds the value of the index in InputLayer's cache
        uint8_t* local_index_ptr;
        
    public:
        using Layer::Layer;
        using PreActivationValueCache::PreActivationValueCache;

        OutputLayer(size_t nodes_number): Layer(nodes_number) , PreActivationValueCache(nodes_number) {}

        void update_node_values(std::vector<float>) override;

        // functions to synch vales with the Input Layer
        //obv the expected outcome will be 1 on the float(th) node and 0 otherwise
        void synch_expected_values(std::vector<float>&&);
        void synch_index(uint8_t*);

        void clear_cached_values();

        float getNodeValueByPosition(size_t) const;
        float getExpectedNodeValueByPosition(size_t) const;

        // I hope I won't mess and confuse myself with this one
        std::vector<float> getExpectedValues() const;
        std::vector<float> getPredictedValues() const;
};

#endif