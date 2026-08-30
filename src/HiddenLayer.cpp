#include <stdexcept>
#include <iostream>

#include "HiddenLayer.hpp"

void HiddenLayer::update_node_values(std::vector<float> new_values){
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