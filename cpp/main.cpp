#include <iostream>
#include <vector>
#include <memory>

#include "include/Matrix.h"
#include "include/UndirectedGraph.h"
#include "include/DirectedGraph.h"

int main(int argc, char** argv) {
    
    std::vector<std::vector<int>> matrix = {
        {0, 1, 0, 0, 0, 0, 0, 0}, // 0
        {0, 0, 1, 0, 0, 0, 0, 0}, // 1
        {0, 0, 0, 0, 0, 0, 0, 0}, // 2
        {0, 0, 0, 0, 1, 0, 0, 0}, // 3
        {1, 0, 1, 0, 0, 0, 0, 0}, // 4
        {0, 1, 0, 0, 0, 0, 0, 0}, // 5
        {0, 0, 0, 0, 0, 0, 0, 0}, // 6
        {1, 0, 0, 0, 0, 0, 0, 0}  // 7
    };

    std::unique_ptr<DirectedGraph> mat;
    try {
        mat = std::make_unique<DirectedGraph>(&matrix);
    } catch(std::logic_error const& e) {
        std::cerr << e.what(); 
        exit(-1);
    }

    std::vector<int> test = mat->toposort(true);
    if (mat->isAcyclic) 
        std::cout << "The graph contains no cycle (The topological ordering of the graph contains all the nodes)\n";
    else 
        std::cout << "The graph contains cycle(s) (The topological ordering of the graph does not contain all the nodes)\n";

    return 0;
}