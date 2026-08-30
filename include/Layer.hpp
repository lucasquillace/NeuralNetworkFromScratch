#ifndef LAYER_HPP
#define LAYER_HPP

#include "Node.hpp"
#include "Matrix.hpp"

#include <vector>
#include <memory>
#include <cstdlib>

#define RAND_V 20
#define RAND_B 40

/*
 * Abstract class that encapsule a single layer of the network
*/
class Layer{
    protected:
        std::vector<Node> nodes;

        static float activation_function(float);

    public:
        //quantity of nodes in the layer
        Layer(int nodes_number): nodes(nodes_number, Node(rand() % RAND_V, rand() % RAND_B)) {}

        virtual void update_node_values(std::vector<float> ) = 0;

        static std::unique_ptr<Matrix> matrixMultiplication(Matrix* , Matrix*);

        std::vector<Node>& getNodes() {return nodes;}
        std::vector<float> getNodeValues();
};


#endif