#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

#include "InputLayer.hpp"

#define FILENAME "dataset/emnist-balanced-train.csv"
#define BATCH_SIZE 10

InputLayer::InputLayer(int nodes_number) : Layer(nodes_number){
    this->node_values_cached.reserve(BATCH_SIZE);
}


void InputLayer::read_from_file(){
    std::ifstream file(FILENAME, std::ifstream::in);

    if (! file.is_open()){
        std::string filename = FILENAME;
        std::filesystem::path p =  std::filesystem::current_path();

        throw std::runtime_error("File " + filename + " does not exist. Working directory: " + p.string()) ;
        exit(0);
    }
    
    this->local_index = 0;
    std::vector<std::string> buffer(BATCH_SIZE);

    //DA FINIRE

}

// I guess it's good to maintain either load_... or update_... . Idk maybe it's used in 2 different scopes
void InputLayer::load_next_training_values(){
    if (local_index == node_values_cached.size()-1){
        this->read_from_file();
    } 
    this->update_node_values(this->node_values_cached[local_index]);
    
}

void InputLayer::update_node_values(std::vector<float> init_values){
    try{
        if (init_values.size() != this->nodes.size()) throw std::runtime_error("Incoherent dimension between nodes quantity ( " + std::to_string(this->nodes.size()) +" ) and values quantity ( " + std::to_string(init_values.size()) + " )");
    }catch(std::runtime_error e){
        std::cout << e.what();
        exit(0);
    }

    for(int i = 0; i < this->nodes.size(); i++){
        this->nodes[i].setValue(init_values[i]);
    }
}
