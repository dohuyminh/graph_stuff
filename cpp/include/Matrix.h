#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

class Matrix {
protected:
    std::vector<std::vector<int>> adj;
    int V, E;
    virtual bool validateGraph() = 0;
    virtual ~Matrix() {};

public:
    Matrix(std::vector<std::vector<int>>* mat);
};

#endif