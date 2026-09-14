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


    public:
        //quantity of nodes in the layer
        Layer(size_t nodes_number): nodes(nodes_number, Node(Layer::activation_function(rand() % RAND_V) , rand() % RAND_B)) {}

        virtual void update_node_values(std::vector<float> ) = 0;

        static std::unique_ptr<Matrix> matrixMultiplication(Matrix* , Matrix*);
        static std::unique_ptr<Matrix> hadamardMultiplication(Matrix*, Matrix*);

        std::vector<Node>& getNodes() {return nodes;}
        std::vector<float> getNodeValues();


        static float activation_function(float);
        static std::vector<float> activation_function(const std::vector<float>&);
        static float derivative_activation_function(float);
        static std::vector<float> derivative_activation_function(const std::vector<float>&);
};


#endif