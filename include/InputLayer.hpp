#ifndef INPUT_LAYER_HPP
#define INPUT_LAYER_HPP

#include <vector>

#include "Layer.hpp"

/*
 * Class that manager the Input Layer and its communication with training and test data.
 * To avoid overhead due to I/O bound tasks, some variables and tricks are stored (the file is red in batches, each one X lines long)
 * last_row_scanned_index is the last row scanned from the file. All the scans must start from here.
 * node_values_cached are the node values scanned previously from the file. This changes on each scan.
 * local_index is the index of the last values given to the network
*/
class InputLayer : public Layer{

    size_t last_row_scanned_index;
    std::vector<std::vector<float>> node_values_cached;
    uint8_t local_index;

    //read the content of nodes from the file located ad dataset/emnist-balanced-train.csv
    void read_from_file();

    public:
        using Layer::Layer;
        InputLayer(int nodes_number);

        // update the node values (from file only if the cached ones are finished)
        void update_node_values(std::vector<float> ) override;

        // loads the next training data to the nodes
        void load_next_training_values();
};

#endif