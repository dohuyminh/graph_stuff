#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

/**
 * Class: Matrix
 * The abstract class representing the adjacency matrix representation of a graph
*/
class Matrix {
protected:
    std::vector<std::vector<int>> adj;
    int V, E;
    static const int NO_EDGE;
    void graphSpecs();
    virtual ~Matrix() {};

public:
    Matrix(std::vector<std::vector<int>>* mat);
};

#endif