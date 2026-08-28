#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iostream>

#include "Layer.hpp"
#include "Node.hpp"
#include "Matrix.hpp"

std::vector<float> Layer::getNodeValues(){
    std::vector<float> values;
    values.reserve(this->nodes.size());

    for (int i = 0; i < nodes.size(); i++){
        values.push_back(this->nodes[i].getValue());
    }

    return values;
}

// does A x B
Matrix Layer::matrixMultiplication(Matrix A, Matrix B){
    try{
        int row_dim = A[0].size();
        for (int i = 0; i < A.size(); i++){
            if (A[i].size() != row_dim){
                throw std::runtime_error("Incoherent dimension of the first matrix. Expected " + std::to_string(row_dim) + " got " + std::to_string(A[i].size()));

            }
        }

        row_dim = B[0].size();
        for (int i = 0; i < B.size(); i++){
            if (B[i].size() != row_dim){
                throw std::runtime_error("Incoherent dimension of the second matrix. Expected " + std::to_string(row_dim) + " got " + std::to_string(B[i].size()));

            }
        }

        if (A[0].size() != B.size()) throw std::runtime_error("Incoherent dimension. First: " + std::to_string(A[0].size()) + " ; second " + std::to_string(B.size()));
    }catch(std::runtime_error e){
        std::cout << e.what();
        exit(0);
    }

    // C's dimension will be A.size() x B[0].size()
    std::vector<std::vector<float>> C;    

    // it should be good for speed
    C.reserve(A.size());
    for (int i = 0; i< A.size(); i++){
        C.push_back(std::vector<float>(B[0].size() , 0));
    }

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < A[0].size(); k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}