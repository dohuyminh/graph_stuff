#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
using std::vector;

/**
 * Class: adjMatrix
 * The Adjajency Matrix representation of an undirected graph; will perform a variety of
 * graph's algorithm via class methods
*/
class adjMatrix {
private:
    vector<vector<int>> adj;

public:
    int V;
    int E;
    
    /**
     * METHOD: Constructor 
     * Creating a new Adjajency Matrix
     * @param adj: The adjacency matrix 
    */
    adjMatrix(vector<vector<int>>& adj) {
        this->adj = adj;
        this->V = adj.size();
        this->E = 0;

        for (auto arc: this->adj)
            for (int v: arc)
                if (v != -1)
                    ++this->E;
    }

    // Find the shortest path
    void dijkstra(int src);
    void floyd_warshall();

    // Find the Minimum Spanning Tree
    void prim(int src);
    void kruskal();
};

#endif