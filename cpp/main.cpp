#include <iostream>
#include <vector>
#include <memory>

#include "include/Matrix.h"
#include "include/UndirectedGraph.h"

int main(int argc, char** argv) {
    
    std::vector<std::vector<int>> matrix = {
        {  0,   4,   8,   0,   0,   0,   0 }, 
        {  4,   0,   9,   8,  10,   0,   0 }, 
        {  8,   9,   0,   2,   0,   1,   0 }, 
        {  0,   8,   2,   0,   7,   9,   0 }, 
        {  0,  10,   0,   7,   0,   5,   6 }, 
        {  0,   0,   1,   9,   5,   0,   2 }, 
        {  0,   0,   0,   0,   6,   2,   0 } 
    };

    std::unique_ptr<UndirectedGraph> mat;

    try {
        mat = std::make_unique<UndirectedGraph>(&matrix);
        mat->kruskal();
    } catch(std::logic_error const& e) {
        std::cout << e.what();
        exit(-1);
    }

    return 0;
}