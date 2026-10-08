cmake_minimum_required(VERSION 3.10)

project(NeuralNetworkProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_compile_options(-Wall -O3)

set(SOURCES
    src/HiddenLayer.cpp
    src/InputLayer.cpp
    src/Layer.cpp
    src/Network.cpp
    src/Node.cpp
    src/OutputLayer.cpp
    src/Matrix.cpp
    src/PreActivationValueCache.cpp
    src/exs/main.cpp  
)

add_executable(NeuralNet ${SOURCES})
add_executable(TestMatrix
    test/test_matrix.cpp
    src/Layer.cpp
    src/Matrix.cpp
    src/Node.cpp
)

target_compile_definitions(NeuralNet PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")