

#include <memory>
#include <iostream>

#include "Network.hpp"
#include "InputLayer.hpp"
#include "OutputLayer.hpp"
#include "HiddenLayer.hpp"
#include "Matrix.hpp"

// Inizializza la rete
Network::Network(int layer_number, std::vector<int> node_number){

    try{
        if ((long unsigned int) layer_number != node_number.size()){
            throw "The number of layer is incoherent with the size of the collection of nodes";
        }
    }catch(const char* m){
        std::cout << m;
        return;
    }

    // instatiate weights and layers

    this->layers.push_back(std::make_unique<InputLayer>(node_number[0]));
    for (int i = 1; i < layer_number -1; i++){
        this->layers.push_back(std::make_unique<HiddenLayer>(node_number[i]));

        this->weights.push_back(std::make_unique<Matrix>(i, i-1));
    }
    this->layers.push_back(std::make_unique<OutputLayer>(node_number[layer_number -1]));

    this->weights.push_back(std::make_unique<Matrix>(layer_number, layer_number -1));
    
}

Network::Network(){
    
    // questo non so quanto abbia senso, sarebbe da cambiare in base a ciò che si vuol fare
    std::vector<int> node_number{2,3,3,1};
    int DEFAULT_LAYER_NUMBER = 4;

    Network(DEFAULT_LAYER_NUMBER, node_number);
}


void Network::feed_forward(){
    for (int index = 1; index < layers.size(); index++){
        std::unique_ptr<Matrix> previous_node_matrix = std::make_unique<Matrix>((this->layers[index-1].get())->getNodeValues());
        std::unique_ptr<Matrix> next_node_matrix = Layer::matrixMultiplication(previous_node_matrix.get(), this->weights[index].get());
        
        std::vector<float> next_nodes_values;

        // if some dimension errors occours, here it's the part of the code I have to look first
        next_nodes_values.reserve(next_node_matrix->getColQuantity());
        for (int i = 0; i< next_node_matrix->getColQuantity(); i++){
            next_nodes_values.push_back(next_node_matrix->getValue(i));
        }

        // va immplementatoa
        layers[index]->update_node_values(std::move(next_nodes_values));
    }
}
