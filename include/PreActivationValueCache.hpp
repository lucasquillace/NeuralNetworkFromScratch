#ifndef PRE_ACTIVATION_VALUE_CACHE_HPP
#define PRE_ACTIVATION_VALUE_CACHE_HPP

#include <vector>
#include "Node.hpp"
/*
 * Idk if I'm doing right or I'm messing everything; hopefully the first one. 
 * This class should be a mixin to save also the pre-activation values during the forward pass,
 * in order to use it in the backprop.
*/
class PreActivationValueCache{
    protected:
        std::vector<Node> pre_activation_nodes;
    public:

        // I don't know if it's a bad idea to initiate the pre_activation_values to 0.
        // Hopeuflly it will make sense in debugging (?)
        PreActivationValueCache(size_t node_qtity): pre_activation_nodes(node_qtity, Node(0, 0)) {}
        virtual std::vector<Node>& getPreActivationNodes() {return this->pre_activation_nodes;}
        virtual std::vector<float> getPreActivationNodesValues();
};

#endif