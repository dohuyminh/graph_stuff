#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

/**
 * Class: Matrix
 * The abstract class representing the adjacency matrix representation of a graph
*/
class Matrix {
protected:
    // All the necessary attributes
    std::vector<std::vector<int>> adj;
    int V, E;
    static const int NO_EDGE;
    
    bool componentHasCycle(int src);

    virtual bool validateGraph() = 0;
    virtual ~Matrix() {};

public:
    // Constructor and operators
    Matrix(std::vector<std::vector<int>>* mat);
    std::vector<int>& operator[](int id);

    // General graph utilities
    void graphSpecs();
    std::vector<int> dfs(int src, std::vector<int>& vis);
    std::vector<int> bfs(int src, std::vector<int>& vis);
};

#endif