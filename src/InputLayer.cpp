#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

#include "InputLayer.hpp"

#define TRAINING_DATA_FILENAME "dataset/emnist-balanced-train.csv"
#define BATCH_SIZE 10

InputLayer::InputLayer(int nodes_number) : Layer(nodes_number), local_index(0), byte_chunk_position(0){
    this->node_values_cached.reserve(BATCH_SIZE);
}

// load the information meaningful to the input layer and pass to the output layer the according expected results
void InputLayer::cache_values(const std::vector<std::string>& buffer, OutputLayer* output_layer){
    std::vector<float> expected_values;
    
    for (int i = 0; i< buffer.size(); i++){
        std::stringstream ss(buffer[i]);
        std::string value;

        std::vector<float> values;
        bool first = true;

        while (std::getline(ss, value, ',')){
            if (first){
                first = false;
                expected_values.push_back((std::stof(value)));

            }else{
                values.push_back(std::stof(value));
            }
        }

        // actually push the BATCH_SIZE expected_values and node_values_cached
        this->node_values_cached.push_back(std::move(values));
    }

    output_layer->synch_expected_values(std::move(expected_values));
}

void InputLayer::read_from_file(OutputLayer* output_layer){
    
    std::ifstream file(TRAINING_DATA_FILENAME, std::ifstream::in);

    if (! file.is_open()){
        std::string filename = TRAINING_DATA_FILENAME;
        std::filesystem::path p =  std::filesystem::current_path();

        throw std::runtime_error("File " + filename + " does not exist. Working directory: " + p.string()) ;
        exit(0);
    }
    
    this->node_values_cached.clear();
    output_layer->clear_cached_values();
    this->local_index = 0;

    std::vector<std::string> buffer(BATCH_SIZE);
    uint8_t lines_read = 0;
    std::string line;

    file.seekg(this->byte_chunk_position);

    while(lines_read < BATCH_SIZE && std::getline(file, line)){
        buffer.push_back(line);
        lines_read++;
    }
    
    this->cache_values(buffer, output_layer);


    if (file.eof()){
        this->byte_chunk_position = -1;
    }else{
        this-> byte_chunk_position = file.tellg();
    }

    // È da manipolare sti dati per capire effetticamente cosa vogliono dire e comunque il primo valore non deve andare nei nodi ma è quello atteso
}

// I guess it's good to maintain either load_... or update_... . Idk maybe it's used in 2 different scopes
void InputLayer::load_next_training_values(OutputLayer* output_layer){

    // to pass the local_index to the OutputLayer
    if (this->byte_chunk_position == 0){
        output_layer->synch_index(&(this->local_index));
    }

    if ((local_index == node_values_cached.size()) || local_index == 0){
        if (this->byte_chunk_position == -1){
            std::cout << "Almost finished training data.";
            this->byte_chunk_position = -2;
        }
        else{
            this->read_from_file(output_layer);
        }
    } 

    // if it's impossible to read new values from file and the cached ones are already been used
    if (this->byte_chunk_position < 0 && (local_index == node_values_cached.size())){
        std::cout << "Finished training data.";
        return;
    }

    this->update_node_values(this->node_values_cached[local_index]);
    this->local_index++;
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
