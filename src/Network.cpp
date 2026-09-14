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

void Network::backprop(){
    
    // because I have to use this at each iteration (and with different dimensions), declaring it here is the best choice
    std::vector<float> delta;
    for(size_t i = 0; i< layers.size(); i++){
        size_t backprop_index = layers.size() - i -1;

        // output layer, first pass
        if (i == 0){
            
            //
            // because the derivative of sigmoid is predicted( 1 -predicted) and
            // because the dericative of binary cross entropy is {predicted - expected}/{predicted(1 - predicted)} 
            // and because we have to compute the product of the 2 derivatives, it's possible to only
            // do the {predicted- expected} part, knowing that the other terms cancel out
            //
            
            Layer* last_layer = this->layers[this->layers.size() -1].get();
            OutputLayer* output_layer = dynamic_cast<OutputLayer*>(last_layer);
            std::vector<float> predicted_values = output_layer->getPredictedValues();
            std::vector<float> expected_values = output_layer->getExpectedValues();
            
            delta.reserve(output_layer->getNodes().size());


            for (size_t j = 0; j< output_layer->getNodes().size(); j ++){
                delta.push_back(predicted_values[i] - expected_values[i]);
            }
            
            // the gradient of weight matrix at [l] is the matrix multiplication between the previous layer activation and the delta
            Matrix prev_weight_matrix_transposted(this->layers[this->layers.size()-2].get()->getNodeValues());
            Matrix delta_matrix(delta.size(), 1, delta);

            std::unique_ptr<Matrix> grad_weight_matrix = Layer::matrixMultiplication(&prev_weight_matrix_transposted, &delta_matrix);

            this->gradient_descent(backprop_index, grad_weight_matrix.get(), &delta_matrix);
        }

        // hidden layers
        else{

            // actually, these are the weights between layer (in -1) and layer (in).
            // For example, in the last hidden layer, these are the weights that connects the last hidden layer to the output layer
            Matrix current_weights_transposted = this->weights[backprop_index +1]->transpose();
            
            // that's the derivative of the activation function with respect to the values of the node
            Layer* layer = this->layers[backprop_index].get();
            HiddenLayer* hidden_layer = dynamic_cast<HiddenLayer*>(layer);
            std::vector<float> derivative_pre_activation = Layer::derivative_activation_function(hidden_layer->getPreActivationNodesValues());
            
            Matrix delta_matrix(1, delta.size(), delta);

            // delta is 1xi(th)_weights_values matrix and current_weights_transposted is i(th)_weight_values x i-1(th)_weight_values
            std::unique_ptr<Matrix> error_derivative = Layer::matrixMultiplication(&delta_matrix, &current_weights_transposted);

            Matrix derivative_pre_activation_matrix( 1 ,derivative_pre_activation.size(), derivative_pre_activation);

            // error_derivative is 1x i-1 (th)_weights_values and so is derivative_pre_activation_matrix
            // and delta_hadamard_p
            std::unique_ptr<Matrix> delta_hadamard_p = Layer::hadamardMultiplication(error_derivative.get(), &derivative_pre_activation_matrix);
            
            // even tho I create a new matrix on each iteration, I have to macke sure to update the delta values (the vector<float>)
            delta.clear();
            size_t new_size = delta_hadamard_p->getColQuantity() * delta_hadamard_p->getRowQuantity();
            delta.reserve(new_size);

            for (size_t i = 0; i< new_size; i++){
                delta.push_back(delta_hadamard_p->getValue(i));
            }

            std::vector<float> post_activation_values = hidden_layer->getNodeValues();
            Matrix post_activation_values_matrix(post_activation_values.size() , 1, post_activation_values);

            // i'm not really sure on these dimensions
            std::unique_ptr<Matrix> weights_gradient = Layer::matrixMultiplication(&post_activation_values_matrix, delta_hadamard_p.get());

            this->gradient_descent(backprop_index, weights_gradient.get(), delta_hadamard_p.get());
        }
    }
}

void Network::gradient_descent(size_t layer_index, Matrix* gradient_weights, Matrix* gradient_bias){

}

float Network::loss_function(float expected, float predicted) const{
    return (expected* log (predicted) + ((1 - expected) * log (1 - predicted)));
}