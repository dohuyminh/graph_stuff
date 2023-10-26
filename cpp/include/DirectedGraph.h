#include "Matrix.h"
#include <vector>

/**
 * TODO: Implement the adjacency matrix representation of
 * Directed Graph, implement the DAG validation and topological sort
*/
class DirectedGraph : public Matrix {
private:
    bool HasNoCycles();
    bool validateGraph() override;

public:
    bool isAcyclic;

    DirectedGraph(std::vector<std::vector<int>>* adj);
    std::vector<int> toposort(bool print_out);
};