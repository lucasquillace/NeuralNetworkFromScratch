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

void OutputLayer::synch_expected_values(std::vector<float>&& values){
    for(int i = 0; i< values.size(); i++){
        std::vector<float> v(this->nodes.size(), 0);
        v[values[i]] = 1;
        this->expected_values.push_back(std::move(v));
    }
}

void OutputLayer::synch_index(uint8_t* index_ptr){
    this-> local_index_ptr = index_ptr;
}

void OutputLayer::clear_cached_values(){
    this->expected_values.clear();
}

float OutputLayer::getExpectedNodeValueByPosition(int pos) const{
    return this->expected_values[*local_index_ptr][pos];
}

float OutputLayer::getNodeValueByPosition(int pos) const{
    return (this->nodes[pos]).getValue();
}