#include "../include/Matrix.h"

Matrix::Matrix(std::vector<std::vector<int>>* adj) {
    this->adj = *adj;
    this->V = adj->size();
    this->E = 0;
    for (auto row: *adj)
        for (const int& n: row)
            if (n != -1)
                ++this->E;
}