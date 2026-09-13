#ifndef HIDDEN_LAYER_HPP
#define HIDDEN_LAYER_HPP

#include <vector>
#include "Layer.hpp"
#include "PreActivationValueCache.hpp"

class HiddenLayer : public Layer, public PreActivationValueCache{

    public:
        using Layer::Layer;
        using PreActivationValueCache::PreActivationValueCache;
        
        HiddenLayer(size_t nodes_number): Layer(nodes_number), PreActivationValueCache(nodes_number) {}
        void update_node_values(std::vector<float>) override;

};

#endif