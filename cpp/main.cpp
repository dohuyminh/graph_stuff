#include <iostream>
#include <vector>

#include "include/Matrix.h"
#include "include/UndirectedGraph.h"

int main(int argc, char** argv) {
    
    std::vector<std::vector<int>> matrix = {
        { -1,   4,   8,  -1,  -1,  -1,  -1 }, 
        {  4,  -1,   9,   8,  10,  -1,  -1 }, 
        {  8,   9,  -1,   2,  -1,   1,  -1 }, 
        { -1,   8,   2,  -1,   7,   9,  -1 }, 
        { -1,  10,  -1,   7,  -1,   5,   6 }, 
        { -1,  -1,   1,   9,   5,  -1,   2 }, 
        { -1,  -1,  -1,  -1,   6,   2,  -1 } 
    };

   UndirectedGraph* mat = new UndirectedGraph(&matrix);

    mat->kruskal();

    delete mat;

    return 0;
}