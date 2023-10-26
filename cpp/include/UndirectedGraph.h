#ifndef ADJ_MATRIX_H_
#define ADJ_MATRIX_H_

#include "Matrix.h"

/**
 * Class: UndirectedGraph
 * The Adjajency Matrix representation of an undirected graph; will perform a variety of
 * graph's algorithm via class methods
*/
class UndirectedGraph : public Matrix {
private:
    bool validateGraph() override;

public:
    /**
     * METHOD: Constructor 
     * Creating a new Adjajency Matrix
     * @param adj: The adjacency matrix 
    */
    UndirectedGraph(std::vector<std::vector<int>>* adj);

    // Find the shortest path
    void dijkstra(int src);
    void floyd_warshall();

    // Find the Minimum Spanning Tree
    void prim(int src);
    void kruskal();
};

#endif