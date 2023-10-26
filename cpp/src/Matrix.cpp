/* --------------------- HEADER FILES AND NAMESPACES --------------------- */

#include "../include/Matrix.h"

#include <iostream>
#include <stack>
#include <queue>

using std::vector;

/* --------------------- PROTECTED METHODS --------------------- */


/**
 * TODO: Implement a method to detect graph's component cycles
*/
bool Matrix::componentHasCycle(int src) {
    
    return false;
}
/* --------------------- PUBLIC METHODS --------------------- */

/**
 * Static attribute representation of having no edge between 2 nodes
*/
const int Matrix::NO_EDGE = 0;

/**
 * METHOD: Constructor
 * Create a new instance of a new adjacency matrix 
 * @param adj: The adjajency matrix
*/
Matrix::Matrix(vector<vector<int>>* adj) {
    this->adj = *adj;
    this->V = adj->size();
    this->E = 0;
    for (auto row: *adj)
        for (const int& n: row)
            if (n != Matrix::NO_EDGE)
                ++this->E;
}


/**
 * METHOD: Operator overloading "[]" 
 * For accessing all the connections from a source node 
 * @param id: The source node ID 
 * @return: The row of the adjacency matrix from that source node
 * @throw std::out_of_range: if the given node ID is beyond the adjacency matrix  
*/
vector<int>& Matrix::operator[](int id) {
    if (id >= this->V || id < 0)
        throw std::out_of_range("The node ID is not present in the graph.\n");
    return this->adj[id];
}

void Matrix::graphSpecs() {
    std::cout << "Graph Details:\n";
    std::cout << "Number of vertices: " << this->V << '\n';
    std::cout << "Number of edges: " << this->E << '\n';
}

/**
 * METHOD: dfs 
 * Give a vector/array representation of the Depth-First Traversal of the graph
 * @param src: The source node to commence the traversal
 * @param vis: The recording array of whether a node has been visited or not
 * @return The vector/array representation of the Depth-First Traversal of the graph 
 * @throw std::out_of_range: In case the given source node ID is not in the graph
*/
vector<int> Matrix::dfs(int src, vector<int>& vis) {
    if (src >= this->V || src < 0)
        throw std::out_of_range("The given node ID is not present in the graph.\n");

    vector<int> res = vector<int>();

    std::stack<int> s = std::stack<int>();
    vis[src] = 1;
    s.push(src);
    res.push_back(src);

    while (!s.empty()) {
        int curr = s.top();
        s.pop();
        vis[curr] = 1;
        for (int i=0; i<this->V; ++i) {
            if (this->adj[curr][i] != Matrix::NO_EDGE && !vis[i]) {
                res.push_back(i);
                s.push(i);
            }
        }
    }

    return res;
}

/**
 * METHOD: bfs 
 * Give a vector/array representation of the Breadth-First Traversal of the graph
 * @param src: The source node to commence the traversal
 * @param vis: The recording array of whether a node has been visited or not
 * @return The vector/array representation of the Breadth-First Traversal of the graph 
 * @throw std::out_of_range: In case the given source node ID is not in the graph
*/
vector<int> Matrix::bfs(int src, vector<int>& vis) {
    if (src >= this->V || src < 0)
        throw std::out_of_range("The given node ID is not present in the graph.\n");

    vector<int> res = vector<int>();
    std::queue<int> q = std::queue<int>();
    vis[src] = 1;
    q.push(src);
    res.push_back(src);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        vis[curr] = 1;
        for (int i=0; i<this->V; ++i) {
            if (this->adj[curr][i] != Matrix::NO_EDGE && !vis[i]) {
                res.push_back(i);
                q.push(i);
            }
        }
    }

    return res;
}