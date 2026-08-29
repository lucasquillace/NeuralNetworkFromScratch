#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iostream>
#include <bits/stdc++.h>

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
std::unique_ptr<Matrix> Layer::matrixMultiplication(Matrix* A, Matrix* B){
    try{
        if (A->getColQuantity() != B->getRowQuantity()) throw std::runtime_error("Incoherent dimension-> First: " + std::to_string(A->getColQuantity()) + " ; second " + std::to_string(B->getRowQuantity()));
    }catch(std::runtime_error e){
        std::cout << e.what();
        exit(0);
    }

    // C's dimension will be """"A->size() x B[0]->size()""""
    std::unique_ptr<Matrix> C = std::make_unique<Matrix>(A->getRowQuantity(), B->getColQuantity());

    // it should be good for speed
    C->clear();

    for (int i = 0; i < A->getRowQuantity(); i++) {
        for (int j = 0; j < B->getColQuantity(); j++) {
            for (int k = 0; k < A->getColQuantity(); k++) {
                float node_value =  
                    (A->getValue(Matrix::convert_dimention(i, k, A->getColQuantity())) + 
                    B->getValue(Matrix::convert_dimention(k , j , B->getColQuantity())));

                C->putValue(Matrix::convert_dimention(i, j, C->getColQuantity()), activation_function(node_value));

            }
        }
    }

    return std::move(C);
}

float Layer::activation_function(float value){
    // sigmoide by default
    return 1/(1+ exp(-value));
}