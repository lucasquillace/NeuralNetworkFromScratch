#ifndef INPUT_LAYER_HPP
#define INPUT_LAYER_HPP

#include <vector>
#include <fstream>

#include "Layer.hpp"
#include "OutputLayer.hpp"

/*
 * Class that manager the Input Layer and its communication with training and test data.
 * To avoid overhead due to I/O bound tasks, some variables and tricks are stored (the file is red in batches, each one X lines long)
 * byte_chunk_position is the first byte to read in a file scan.
 * node_values_cached are the node values scanned previously from the file. This changes on each scan.
 * local_index is the index of the last values given to the network
 * 
 * The first layer has 784 nodes
*/
class InputLayer : public Layer{

    private:
        // position of the last byte red. -1 when hit EOF, -2 when invalid
        std::streampos byte_chunk_position;
        std::vector<std::vector<float>> node_values_cached;
        uint8_t local_index;

        //read the content of nodes from the file located ad dataset/emnist-balanced-train.csv
        void read_from_file(OutputLayer* );

        void cache_values(const std::vector<std::string>&, OutputLayer*);

    public:
        using Layer::Layer;
        InputLayer(int nodes_number);

        // update the node values (from file only if the cached ones are finished)
        void update_node_values(std::vector<float> ) override;

        // loads the next training data to the nodes (N.B.: call update_node_values in background).
        void load_next_training_values(OutputLayer* );

        // loads the test data to the nodes
        void load_next_test_values(OutputLayer* );
};

#endif