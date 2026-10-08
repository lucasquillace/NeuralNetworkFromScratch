#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cmath>

#include "Layer.hpp"
#include "Node.hpp"
#include "Matrix.hpp"

std::vector<float> Layer::getNodeValues(){
    std::vector<float> values;
    values.reserve(this->nodes.size());

    for (size_t i = 0; i < nodes.size(); i++){
        values.push_back(this->nodes[i].getValue());
    }

    return values;
}

// does A x B
std::unique_ptr<Matrix> Layer::matrixMultiplication(Matrix* A, Matrix* B){
    try{
        if (A->getColQuantity() != B->getRowQuantity()) throw std::runtime_error("Incoherent dimension for matrix multiplication.\n -> First: " + std::to_string(A->getColQuantity()) + " ; second " + std::to_string(B->getRowQuantity()));
    }catch(const std::runtime_error& e){
        std::cout << e.what();
        exit(0);
    }

    // C's dimension will be """"A->size() x B[0]->size()""""
    std::unique_ptr<Matrix> C = std::make_unique<Matrix>(A->getRowQuantity(), B->getColQuantity());

    for (size_t i = 0; i < A->getRowQuantity(); i++) {
        for (size_t j = 0; j < B->getColQuantity(); j++) {
            float node_value = 0;
            for (size_t k = 0; k < A->getColQuantity(); k++) {
                node_value +=  
                    (A->getValue(Matrix::convert_dimention(i, k, A->getColQuantity())) * 
                    B->getValue(Matrix::convert_dimention(k , j , B->getColQuantity())));

            }
            C->putValue(Matrix::convert_dimention(i, j, C->getColQuantity()), node_value);
        }
    }

    // Purpousely don't using std::move to use Named Return Value Optimization. It should be faster
    return C;
}

// does A x B but in hadamard way (not 'dot product' but element-wise)
std::unique_ptr<Matrix> Layer::hadamardMultiplication(Matrix* A, Matrix* B){
    try{
        if ((A->getColQuantity() != B->getColQuantity()) || (A->getRowQuantity() != B-> getRowQuantity())) throw std::runtime_error("Incoherent dimension for hadamard multiplication.\n -> First dimension: (" + std::to_string(A->getRowQuantity()) + "x" + std::to_string(A->getColQuantity()) + "). \n  -> Second dimension: (" + std::to_string(B->getRowQuantity()) + "x" + std::to_string(B->getColQuantity()) + ").");
    }catch(const std::runtime_error& e){
        std::cout << e.what();
        exit(0);
    }

    std::unique_ptr<Matrix> C = std::make_unique<Matrix>(A->getRowQuantity(), A->getColQuantity());
    size_t c_size = A->getColQuantity() * A->getRowQuantity();
    
    for (size_t i = 0; i< c_size; i++){
        C->putValue(i, (A->getValue(i) * B->getValue(i)));
    }

    return C;
}

float Layer::activation_function(float value){
    // sigmoid by default
    return 1/(1+ exp(-value));
}

std::vector<float> Layer::activation_function(const std::vector<float>& values){
    std::vector<float> new_values;
    new_values.reserve(values.size());
    for (size_t i = 0; i< values.size(); i++){
        new_values.push_back(Layer::activation_function(values[i]));
    }
    return new_values;
}

float Layer::derivative_activation_function(float value){
    return value * (1.0 - value);
}

std::vector<float> Layer::derivative_activation_function(const std::vector<float>& values){
    std::vector<float> new_values;
    new_values.reserve(values.size());
    for (size_t i = 0; i< values.size(); i++){
        new_values.push_back(Layer::derivative_activation_function(values[i]));
    }
    return new_values;
}