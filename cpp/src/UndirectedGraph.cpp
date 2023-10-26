/* --------------------- HEADER FILES INCLUDES --------------------- */

#include "../include/UndirectedGraph.h"
#include "../include/DisjointSet.h"

#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <exception>

/* --------------------- NAMESPACES & TEMPLATES --------------------- */

using std::cout, std::cerr, std::cin, std::fill, std::setw, std::setfill, std::vector;

typedef std::pair<int, int> intPair;
typedef std::tuple<int, int, int> intTup;

template<typename T> void printElement(T t, const int& width, const char& separator) {
    cout << std::right << setw(width) << setfill(separator) << t;
}

/* --------------------- PRIVATE METHODS --------------------- */

/**
 * METHOD: UndirectedGraph::validateGraph
 * @return if the graph is an undirected graph or not 
*/
bool UndirectedGraph::validateGraph() {
    if (!(this->adj.size() > 0 && this->adj.size() == this->adj[0].size()))
        return false;
    
    int V=this->adj.size();
    for (int i=0; i<V; ++i) 
        for (int j=i; j<V; ++j)
            if (this->adj[i][j] != this->adj[j][i])
                return false;
    return true;
}

/* --------------------- PUBLIC METHODS --------------------- */

/**
 * METHOD: Constructor
 * Create an instance of an adjajency matrix 
 * @throw std::logic_error: if the given adjacency matrix is not the representation of an undirected graph
*/
UndirectedGraph::UndirectedGraph(vector<vector<int>>* adj) : Matrix(adj) {
    // Check if the graph is actually undirected or not; if not, then delete the adjacency matrix and throw an exception
    if (!this->validateGraph()) {
        throw std::logic_error("The adjajency matrix is not a representation of an undirected graph\n");
    }
    this->E /= 2;
}

/**
 * METHOD: dijkstra
 * Gives the shortest distance from one node to the rest of the graph using
 * Dijkstra's Algorithm
 * @param src: The source node
*/
void UndirectedGraph::dijkstra(int src) {
    // Validate the source node
    if (src < 0 || src >= this->V) {
        cerr << "Not a valid node ID for source\n";
        return;
    }
    
    // Distance array; keeping track of the distance from the source node  
    int dist[this->V];
    fill(dist, dist+this->V, INT_MAX);
    dist[src] = 0;

    // Visited array; keeping track of whether the node is visited or not 
    bool vis[this->V];
    fill(vis, vis+this->V, false);

    // Initualize the priority queue (min heap based on the edge weight) 
    std::priority_queue<intPair, vector<intPair>, std::greater<intPair>> pq
        = std::priority_queue<intPair, vector<intPair>, std::greater<intPair>>();

    // Previous array: keeping track of what node comes before in the shortest path
    int prev[this->V];
    fill(prev, prev+this->V, Matrix::NO_EDGE);

    pq.push({0, src});
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        // Extract the current node
        int u = curr.second;
        vis[u] = true;

        // Iterate through every neighboring nodes 
        for (int v=0; v<this->V; ++v) {
            if (this->adj[u][v] == Matrix::NO_EDGE || vis[v])
                continue;

            // If the new distance is smaller than the current recorded distance --> Update the smallest edge and the path
            int tmp = dist[u] + this->adj[u][v];
            if (tmp < dist[v]) {
                dist[v] = tmp;
                prev[v] = u;
            }
            pq.push({dist[v], v});
        }
    }

    this->graphSpecs();
    cout << "Performing Dijkstra's Algorithm on the graph gives:\n";
    int idWidth = 7, distWidth = 8, prevWidth = 8;
    char seperator = ' ';
    cout << "Node ID   " << "   Distance   " << "   Previous" << '\n';
    for (int i=0; i<this->V; ++i) {
        printElement(i, idWidth, seperator);
        cout << "      ";
        printElement(dist[i], distWidth, seperator);
        cout << "      ";
        printElement(prev[i], prevWidth, seperator);
        cout << '\n';
    }
    cout << "Source: " << src << '\n';
}

/**
 * METHOD: floyd_warshall
 * Gives the tables of the shortest paths from all nodes to all other nodes
 * Based on Floyd-Warshall's Algorithm
*/
void UndirectedGraph::floyd_warshall() {
    // Creating a new 2D matrix copy of the graph; replacing Matrix::NO_EDGE with INT_MAX to make the algorithm work
    vector<vector<int>> dist(this->adj);
    for (int i=0; i<this->V; ++i) {
        for (int j=0; j<this->V; ++j) {
            if (dist[i][j] == Matrix::NO_EDGE)
                dist[i][j] = INT_MAX;
            if (i == j)
                dist[i][j] = 0;
        }
    }

    // Previous path; same purpose as the previous array from Djikstra's, but in a 2D matrix
    int path[this->V][this->V];
    for (int i=0; i<this->V; ++i)
        for (int j=0; j<this->V; ++j)
            path[i][j] = (dist[i][j] == INT_MAX || dist[i][j] == 0) ? INT_MAX : j;
 
    // Looping through every middle nodes
    for (int i=0; i<this->V; ++i)
        // Looping through every start node
        for (int s=0; s<this->V; ++s)
            //Looping through every end node 
            for (int e=0; e<this->V; ++e)
                // Update the shortest path 
                if (
                    dist[s][i] != INT_MAX && 
                    dist[i][e] != INT_MAX &&
                    dist[s][e] > dist[s][i] + dist[i][e]
                ) {
                    dist[s][e] = dist[s][i] + dist[i][e];
                    path[s][e] = i; 
                }

    // Return the INT_MAX to Matrix::NO_EDGE for printing
    for (int i=0; i<this->V; ++i)
        for (int j=0; j<this->V; ++j) {
            if (dist[i][j] == INT_MAX)
                dist[i][j] = Matrix::NO_EDGE;    
            if (path[i][j] == INT_MAX)
                path[i][j] = Matrix::NO_EDGE;
        }

    this->graphSpecs();
    cout << "Performing Floyd-Warshall's Algorithm on the graph gives:\n";
    cout << "Minimum distance from source to destination node:\n";
    cout << "   From:  ";
    for (int i=0; i<this->V; ++i)
        printElement(i, 6, ' ');
    cout << '\n';
    for (int i=0; i<this->V; ++i) {
        cout << "To: ";
        printElement(i, 6, ' ');
        for (int j=0; j<this->V; ++j) {
            printElement(dist[i][j], 6, ' ');
        }
        cout << '\n';
    }
    cout << "The path with the least weight from source to destination node:\n";
    cout << "   From:  ";
    for (int i=0; i<this->V; ++i)
        printElement(i, 6, ' ');
    cout << '\n';
    for (int i=0; i<this->V; ++i) {
        cout << "To: ";
        printElement(i, 6, ' ');
        for (int j=0; j<this->V; ++j) {
            printElement(path[i][j], 6, ' ');
        }
        cout << '\n';
    }
}

/**
 * METHOD: prim_algo
 * This will print out a table containing the edges needed to construct the Minimum Spanning Tree
 * @param src: The source node of the MST
*/
void UndirectedGraph::prim(int src) {
    // Validate the source node 
    if (src < 0 || src >= this->V) {
        cerr << "Not a valid node ID for source\n";
        return;
    }
    
    // Visited array; keeping track of what node has already in the tree
    bool vis[this->V];
    fill(vis, vis+V, false);

    // Distance array: keeping track of the smallest edge connecting to the end node
    int dist[this->V];
    fill(dist, dist+this->V, INT_MAX);

    // Previous array: keeping track of the node connecting to the other node with the smallest edge
    int prev[this->V];
    fill(prev, prev+this->V, Matrix::NO_EDGE);
    prev[src] = -1;

    dist[src] = 0;

    // Initialize the priority queue (min heap)
    std::priority_queue<intPair, vector<intPair>, std::greater<intPair>> pq
        = std::priority_queue<intPair, vector<intPair>, std::greater<intPair>>();

    pq.push({0, src});
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        // Extract the current assessing node; mark it as part of the tree
        int u=curr.second;
        vis[u]=true;

        // Iterate through its neighbors 
        for (int v=0; v<this->V; ++v) {
            // Not a neighbor
            if (this->adj[u][v] == Matrix::NO_EDGE)
                continue;

            // If the neighbor is not part of the tree and the edge is smaller than the current recorded distance --> Join them
            if (!vis[v] && dist[v] > this->adj[u][v]) {
                dist[v] = this->adj[u][v];
                pq.push({dist[v], v});
                prev[v] = u;
            }
        }        
    }

    this->graphSpecs();
    int density = 0;
    cout << "Performing Prim's Algorithm on the graph gives the Minimum Spanning Tree:\n";
    int idWidth = 7, distWidth = 8, prevWidth = 8;
    char seperator = ' ';
    cout << "Node ID   " << "   Distance   " << "   Previous" << '\n';
    for (int i=0; i<this->V; ++i) {
        printElement(i, idWidth, seperator);
        cout << "      ";
        printElement(dist[i], distWidth, seperator);
        cout << "      ";
        if (dist[i] != Matrix::NO_EDGE)
            density += dist[i];
        printElement(prev[i], prevWidth, seperator);
        cout << '\n';
    }
    cout << "Source: " << src << '\n';
    cout << "Density of MST: " << density << '\n';
}

/**
 * METHOD: kruskal
 * Gives all the edges needed to construct a Minimum Spanning Tree
 * Using Kruskal's Algorithm
*/
void UndirectedGraph::kruskal() { 
    vector<intTup> Edges = vector<intTup>();
    
    // Collect all the valid edges
    for (int i=0; i<this->V; ++i)
        for (int j=i+1; j<this->V; ++j)
            if (this->adj[i][j] != Matrix::NO_EDGE)
                Edges.push_back({this->adj[i][j], i, j});

    // Sort the edges by weight
    std::sort(Edges.begin(), Edges.end());

    // Initialize the disjoint set
    DisjointSet* S = new DisjointSet(this->V);
    
    // MST Density
    int density = 0;

    this->graphSpecs();
    cout << "Performing Kruskal's Algorithm on the graph gives the following Minimum Spanning Tree:\n";

    // Looping through all the edges
    for (auto Edge: Edges) {
        // We've found all the edges to connect into a single tree; exit
        if (S->n_sets == 1)
            break;

        /*
            The edge is as following:
                 w
            u -------> v
        */
        int w = std::get<0>(Edge);
        int u = std::get<1>(Edge);
        int v = std::get<2>(Edge);

        // The set representation of each vertex
        int src1 = S->find(u);
        int src2 = S->find(v);        

        // These 2 are the same set; connecting them will form a cycle
        if (src1 == src2)
            continue;
        
        // Merging the set together; the set with lower rank will be the subtree of the other set
        int r1 = S->rank(src1), r2 = S->rank(src2);
        (r1 < r2) ? S->merge(src1, src2) : S->merge(src2, src1);

        cout << "Adding edge " << u << " -- " << v << " of weight " << w << '\n';

        // Increment the current density of the MST
        density += w;
    }

    cout << "Density: " << density << '\n';

    delete S;
}