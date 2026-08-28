#ifndef LAYER_HPP
#define LAYER_HPP

#include "Node.hpp"

#include <vector>
#include <memory>
#include <cstdlib>

#define RAND_V 20
#define RAND_B 40

class Node;

/*
 * Abstract class that encapsule a single layer of the network
*/
class Layer{
    protected:
        std::vector<Node> nodes;

    public:
        //quantità di nodi nel layer
        Layer(int nodes_number): nodes(nodes_number, Node(rand() % RAND_V, rand() % RAND_B)) {}

        // trova i valori del layer basandosi sul layer precedente. In caso di Input Layer, prende i valori dal dataset
        virtual void update_node_values(std::vector<float> ) = 0;

        static Matrix matrixMultiplication(Matrix , Matrix);

        std::vector<Node> getNodes() {return nodes;}
        std::vector<float> getNodeValues();
};


#endif