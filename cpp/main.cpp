#include <iostream>
#include <vector>
#include <memory>

#include "include/Matrix.h"
#include "include/UndirectedGraph.h"
#include "include/DirectedGraph.h"

int main(int argc, char** argv) {
    
    std::vector<std::vector<int>> matrix = {
        {0, 1, 3, 0}, 
        {1, 0, 1, 0}, 
        {3, 1, 0, 1}, 
        {0, 0, 1, 0}
    };

    std::unique_ptr<UndirectedGraph> mat;
    try {
        mat = std::make_unique<UndirectedGraph>(&matrix);
        std::vector<std::vector<int>> prompt = mat->kruskal();
    } catch (std::logic_error const& e) {
        std::cerr << e.what();
        exit(-1);
    }

    return 0;
}