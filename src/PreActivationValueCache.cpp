#include "PreActivationValueCache.hpp"

std::vector<float> PreActivationValueCache::getPreActivationNodesValues(){
    std::vector<float> v;
    v.reserve(this->pre_activation_nodes.size());
    for (size_t i = 0; i< pre_activation_nodes.size(); i++){
        v.push_back(this->pre_activation_nodes[i].getValue());
    }
    return v;
}