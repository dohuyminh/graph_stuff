#ifndef DISJOINT_SET_H_
#define DISJOINT_SET_H_

/**
 * Class: DisjointSet
 * The implementation of a Disjoint Set, using rank-by-union and path compression
 * 
 * Negative numbers in the set array indicates the element is the representation of
 * the set, and positive numbers means it is the parent of the element
 * 
 * Given an array:
 * [-2, -1, 0]
 *  0   1   2
 * 
 * This indicates 2 existing sets: 
 * Set 1 is represented by 1, and has abs(-1) = 1 element: {1}
 * Set 2 is represented by 0, and has abs(-2) = 2 elements: {0, 2} 
*/
class DisjointSet {
private:
    int* set;

public:
    int n_sets;
    DisjointSet(int n);
    ~DisjointSet();

    int find(int id);
    int rank(int id);
    void merge(int src, int dest);
};

#endif