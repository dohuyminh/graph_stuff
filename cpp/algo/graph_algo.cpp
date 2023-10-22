#include "matrix.h"
#include "DisjointSet.h"

#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <iomanip>

using std::cout, std::cerr, std::cin, std::fill, std::setw, std::setfill;

typedef std::pair<int, int> intPair;
typedef std::tuple<int, int, int> intTup;

template<typename T> void printElement(T t, const int& width, const char& separator) {
    cout << std::right << setw(width) << setfill(separator) << t;
}

/**
 * METHOD: dijkstra
 * Gives the shortest distance from one node to the rest of the graph using
 * Dijkstra's Algorithm
 * @param src: The source node
*/
void adjMatrix::dijkstra(int src) {
    if (src < 0 || src >= this->V) {
        cerr << "Not a valid node ID for source\n";
        return;
    }
    
    int dist[this->V];
    fill(dist, dist+this->V, INT_MAX);
    dist[src] = 0;

    bool vis[this->V];
    fill(vis, vis+this->V, false);

    dist[src] = 0;
    std::priority_queue<intPair, vector<intPair>, std::greater<intPair>> pq
        = std::priority_queue<intPair, vector<intPair>, std::greater<intPair>>();

    int prev[this->V];
    fill(prev, prev+this->V, -1);

    pq.push({0, src});
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        int u = curr.second;

        vis[u] = true;

        for (int v=0; v<this->V; ++v) {
            if (this->adj[u][v] == -1 || vis[v])
                continue;

            int tmp = dist[u] + this->adj[u][v];
            if (tmp < dist[v]) {
                dist[v] = tmp;
                prev[v] = u;
            }
            pq.push({dist[v], v});
        }
    }

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
void adjMatrix::floyd_warshall() {
    vector<vector<int>> dist(this->adj);
    for (int i=0; i<this->V; ++i) {
        for (int j=0; j<this->V; ++j) {
            if (dist[i][j] == -1)
                dist[i][j] = INT_MAX;
            if (i == j)
                dist[i][j] = 0;
        }
    }

    int path[this->V][this->V];
    for (int i=0; i<this->V; ++i)
        for (int j=0; j<this->V; ++j)
            path[i][j] = (dist[i][j] == INT_MAX || dist[i][j] == 0) ? INT_MAX : j;
 
    for (int i=0; i<this->V; ++i)
        for (int s=0; s<this->V; ++s)
            for (int e=0; e<this->V; ++e)
                if (
                    dist[s][i] != INT_MAX && 
                    dist[i][e] != INT_MAX &&
                    dist[s][e] > dist[s][i] + dist[i][e]
                ) {
                    dist[s][e] = dist[s][i] + dist[i][e];
                    path[s][e] = i; 
                }

    for (int i=0; i<this->V; ++i)
        for (int j=0; j<this->V; ++j) {
            if (dist[i][j] == INT_MAX)
                dist[i][j] = -1;    
            if (path[i][j] == INT_MAX)
                path[i][j] = -1;
        }

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
void adjMatrix::prim(int src) {
    if (src < 0 || src >= this->V) {
        cerr << "Not a valid node ID for source\n";
        return;
    }
    
    bool vis[this->V];
    fill(vis, vis+V, false);

    int dist[this->V];
    fill(dist, dist+this->V, INT_MAX);

    int prev[this->V];
    fill(prev, prev+this->V, -1);

    dist[src] = 0;

    std::priority_queue<intPair, vector<intPair>, std::greater<intPair>> pq
        = std::priority_queue<intPair, vector<intPair>, std::greater<intPair>>();

    pq.push({0, src});
    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();

        int u=curr.second;
        vis[u]=true;

        for (int v=0; v<this->V; ++v) {
            if (this->adj[u][v] == -1)
                continue;
            if (!vis[v] && dist[v] > this->adj[u][v]) {
                dist[v] = this->adj[u][v];
                pq.push({dist[v], v});
                prev[v] = u;
            }
        }        
    }

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
        if (dist[i] != -1)
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
void adjMatrix::kruskal() { 
    vector<intTup> Edges = vector<intTup>();
    
    // Collect all the valid edges
    for (int i=0; i<this->V; ++i)
        for (int j=i+1; j<this->V; ++j)
            if (this->adj[i][j] != -1)
                Edges.push_back({this->adj[i][j], i, j});

    // Sort the edges by weight
    std::sort(Edges.begin(), Edges.end());

    // Initialize the disjoint set
    DisjointSet* S = new DisjointSet(this->V);
    
    // MST Density
    int density = 0;


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
}