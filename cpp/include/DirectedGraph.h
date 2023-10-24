#include "Matrix.h"

/**
 * TODO: Implement the adjacency matrix representation of
 * Directed Graph, implement the DAG validation and topological sort
*/
class DirectedGraph : public Matrix {
private:
    bool isAcyclic();

public:
    void toposort();
};