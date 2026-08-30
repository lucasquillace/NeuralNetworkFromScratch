#include <iostream>
#include <stdexcept>

#include "OutputLayer.hpp"

void OutputLayer::update_node_values(std::vector<float> new_values){
    try{
        if (new_values.size() != this->nodes.size()) throw std::runtime_error("Incoherent dimension between layer ( " + std::to_string(this->nodes.size()) + " ) and new values ( " + std::to_string(new_values.size()) + " )." );
    }catch (std::runtime_error e ){
        std::cout << e.what();
        exit(0);
    }

    for (int i = 0; i< this->nodes.size(); i++){
        this->nodes[i].setValue(new_values[i]);
    }
}

// add the expected value to its cache. expected_values is synchronized with InputLayer.node_value_cached:
// Hence the expected output ad InputLayer.nodes_value_cached[i] is expected_values[i]
void OutputLayer::push_expected_value(float value){
    std::vector<float> values(this->nodes.size(), 0);
    values[value] = 1;
    this->expected_values.push_back(std::move(values));
}