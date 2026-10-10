#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <thread>

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

// helper to concurrenty do mat_mul. A thread multiply from [th_id * batch_size] to [(th_id+1) * batch_size - 1]
// It simply splits the first matrix in max_thread batches and does a matrix multiplication. I don't think I need mutex (?)
void _mul_helper(Matrix* C, Matrix* A, Matrix* B, size_t start_row_index, size_t end_row_index){
    for (size_t i = start_row_index; i < end_row_index; i++) {
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
    uint16_t th_available = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(th_available);
    
    // if I'm lucky, all threads share the same amount of work. Otherwise, the last one has a batch size equal to the remaining of the division
    uint16_t batch_size = A->getRowQuantity() / th_available;
    uint16_t last_batch = 0;

    if (A->getRowQuantity() % th_available != 0){
        last_batch = A ->getRowQuantity() % th_available;
    }

    for(uint16_t i = 0; i< th_available; i++){
        threads.push_back(std::thread(_mul_helper, C.get(), A, B, i*batch_size, ((i+1) * batch_size)));

        if (i == (th_available -2) && last_batch != 0){
            threads.push_back(std::thread(_mul_helper, C.get(), A, B, i*batch_size, (i*batch_size) + last_batch));
            break;
        }
    }

    for(uint16_t i = 0; i< th_available; i++){
        threads[i].join();
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