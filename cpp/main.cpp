#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>

#include "include/Matrix.h"
#include "include/UndirectedGraph.h"
#include "include/DirectedGraph.h"

int main(int argc, char** argv) {

    std::vector<std::vector<int>> mat = {
        {0, 1, 3, 0}, 
        {1, 0, 1, 0}, 
        {3, 1, 0, 1}, 
        {0, 0, 1, 0}
    };

    std::unique_ptr<UndirectedGraph> G;
    try {
        G = std::make_unique<UndirectedGraph>(&mat);
        std::vector<std::vector<int>> prompt = G->dijkstra(0);
    } catch (std::logic_error const& e) {
        std::cerr << e.what() << '\n';
        exit(-1);
    }

    return 0;
}
