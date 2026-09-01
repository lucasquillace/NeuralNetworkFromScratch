#include <cmath>
#include <memory>
#include <iostream>

#include "Network.hpp"
#include "InputLayer.hpp"
#include "OutputLayer.hpp"
#include "HiddenLayer.hpp"
#include "Matrix.hpp"

// Inizializza la rete
Network::Network(size_t layer_number, std::vector<size_t> node_number){

    try{
        if (layer_number != node_number.size()){
            throw "The number of layer is incoherent with the size of the collection of nodes";
        }
    }catch(const char* m){
        std::cout << m;
        return;
    }

    // instatiate weights and layers

    this->layers.push_back(std::make_unique<InputLayer>(node_number[0]));
    for (size_t i = 1; i < layer_number -1; i++){
        this->layers.push_back(std::make_unique<HiddenLayer>(node_number[i]));

        this->weights.push_back(std::make_unique<Matrix>(i, i-1));
    }
    this->layers.push_back(std::make_unique<OutputLayer>(node_number[layer_number -1]));

    this->weights.push_back(std::make_unique<Matrix>(layer_number, layer_number -1));
    
}


void Network::feed_forward(){
    for (size_t index = 1; index < layers.size(); index++){
        std::unique_ptr<Matrix> previous_node_matrix = std::make_unique<Matrix>((this->layers[index-1].get())->getNodeValues());
        std::unique_ptr<Matrix> next_node_matrix = Layer::matrixMultiplication(previous_node_matrix.get(), this->weights[index].get());
        
        std::vector<float> next_nodes_values;

        // if some dimension errors occours, here it's the part of the code I have to look first
        next_nodes_values.reserve(next_node_matrix->getColQuantity());
        for (size_t i = 0; i< next_node_matrix->getColQuantity(); i++){
            next_nodes_values.push_back(next_node_matrix->getValue(i));
        }

        layers[index]->update_node_values(std::move(next_nodes_values));
    }
}

float Network::cost(){
    // loss between OutputLayer.expected_values[*local_index_ptr] and this->...->nodes(.getValue())
    Layer* last_layer = this->layers[this->layers.size()-1].get();
    OutputLayer* outputLayer = dynamic_cast<OutputLayer*>(last_layer);
    float total_cost = 0;
    
    for(size_t i = 0; outputLayer->getNodes().size() ; i++){
        float predicted = outputLayer->getNodeValueByPosition(i);
        float expected = outputLayer->getExpectedNodeValueByPosition(i);
        total_cost += loss_function(expected, predicted);
    }

    return ( -(total_cost / outputLayer->getNodes().size()));
}

float Network::loss_function(float expected, float predicted) const{
    return (expected* log (predicted) + ((1 - expected) * log (1 - predicted)));
}