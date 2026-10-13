#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>

#include "Layer.hpp"
#include "Matrix.hpp"


void test_multiplication_correctness(){
    std::vector<float> a_value = {3.0, 5.0, 6.0, 5.0, 7.0, 9.0};
    std::vector<float> b_value = {3.0, 8.0, 4.0, 4.0, 3.0, 5.0};

    int a_col = 3;
    int b_col = 2;

    Matrix A(a_col, b_col, a_value);
    Matrix B(b_col, a_col, b_value);

    std::unique_ptr<Matrix> C = Layer::matrixMultiplication(&A, &B);

    for (size_t i = 0; i < C->getRowQuantity(); i++){
        for (size_t j = 0; j < C->getColQuantity(); j++)
            std::cout << C->getValue(Matrix::convert_dimention(i, j, C->getColQuantity())) << " ";
        std::cout << "\n";
    }

}

void test_timing() {
    size_t N = 1000;

    std::vector<float> a_values(N*N), b_values(N*N);
    for (auto& v : a_values) v = rand() % 10;
    for (auto& v : b_values) v = rand() % 10;

    Matrix A(N, N, a_values);
    Matrix B(N, N, b_values);

    auto start = std::chrono::high_resolution_clock::now();

    std::unique_ptr<Matrix> C = Layer::matrixMultiplication(&A, &B);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "NxN = " << N << "took: " << duration.count() << "ms\n";
}

int main(){
    test_multiplication_correctness();
    test_timing();
}