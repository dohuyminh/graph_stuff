/* --------------------- HEADER FILES AND NAMESPACES --------------------- */

#include "../include/DirectedGraph.h"
#include <iostream>
#include <exception>
#include <queue>

using std::vector, std::cout;

/* --------------------- PRIVATE METHODS --------------------- */

bool DirectedGraph::validateGraph() {
    return this->adj.size() > 0 && this->adj.size() == this->adj[0].size();
}

/**
 * METHOD: isAcyclic
 * Check if the given graph is acyclic or not, based on the Topological ordering 
 * of the graph
 * @return: whether the graph contains no cycle 
*/
bool DirectedGraph::HasNoCycles() {
    
    // If the graph is truly acyclic, the topological ordering 
    // of the graph should retain all the nodes, and not the 
    // subgraph at which no cycle is found
    vector<int> sorted = this->toposort(false);
    return (int)sorted.size() == this->V;
}

/* --------------------- PUBLIC METHODS --------------------- */

/**
 * METHOD: Constructor
 * Create an instance of adjacency matrix for a directed graph
 * @param adj: The adjacency matrix
 * @throw std::logic_error: if the given matrix is not a adjacency matrix representation of a graph
*/
DirectedGraph::DirectedGraph(vector<vector<int>>* adj): Matrix(adj) {
    if (!this->validateGraph()) 
        throw std::logic_error("The matrix is not the adjajency matrix representation of a graph\n");

    this->isAcyclic = this->HasNoCycles();
}


/**
 * METHOD: toposort
 * Return the array/vector representation of the topological ordering of the graph
 * Using Breadth-First Traversal
 * @param print_out: whether to display the ordering to stdout or not 
 * @return The Topological ordering of the graph 
*/
vector<int> DirectedGraph::toposort(bool print_out) {
    // The result vector/array
    vector<int> res = vector<int>();
    
    // Construct the in-degree array
    int indeg[this->V] = {0};
    for (int u=0; u<this->V; ++u)
        for (int v=0; v<this->V; ++v)
            if (this->adj[u][v] != Matrix::NO_EDGE)
                ++indeg[v];

    // Implementation is Breadth-First based, so a queue
    std::queue<int> bfs = std::queue<int>();
    
    // Standard BFS procedure; but now instead of the source node, start with all nodes 
    // With in-degree of 0
    for (int n=0; n<this->V; ++n)
        if (indeg[n]==0)
            bfs.push(n);

    // Start the traversal
    while (!bfs.empty()) {
        int u = bfs.front();
        bfs.pop();

        res.push_back(u);

        for (int v=0; v<this->V; ++v) {
            if (this->adj[u][v] == Matrix::NO_EDGE)
                continue;

            --indeg[v];
            if (indeg[v] == 0)
                bfs.push(v);
        }
    }

    if (print_out) {
        this->graphSpecs();
        cout << "The Topological Sorting of the given graph is as following:\n";
        for (int n: res)
            cout << n << ' ';
        cout << '\n';
    }

    return res;
}