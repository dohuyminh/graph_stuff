#include "../include/Matrix.h"

#include <iostream>

/**
 * METHOD: Constructor
 * Create a new instance of a new adjacency matrix 
 * @param adj: The adjajency matrix
*/
Matrix::Matrix(std::vector<std::vector<int>>* adj) {
    this->adj = *adj;
    this->V = adj->size();
    this->E = 0;
    for (auto row: *adj)
        for (const int& n: row)
            if (n != Matrix::NO_EDGE)
                ++this->E;
}

const int Matrix::NO_EDGE = 0;

void Matrix::graphSpecs() {
    std::cout << "Graph Details:\n";
    std::cout << "Number of vertices: " << this->V << '\n';
    std::cout << "Number of edges: " << this->E << '\n';
}