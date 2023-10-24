#include "../include/DisjointSet.h"

#include <algorithm>

/**
 * METHOD: Constructor
 * Gives n different disjoint sets
*/
DisjointSet::DisjointSet(int n) {
    this->set = new int[n];
    std::fill(this->set, this->set+n, -1);
    this->n_sets = n;
}

/**
 * METHOD: Destructor
 * Delete the set array
*/
DisjointSet::~DisjointSet() {
    delete[] this->set;
}

/**
 * METHOD: find
 * Gives the set representation given an element
 * @param id: The element 
 * @return The set representation of the element
*/
int DisjointSet::find(int id) {
    for (; this->set[id] >= 0; id = this->set[id]);
    return id;
}

/**
 * METHOD: rank
 * Gives the rank of the set given the element
 * @param id: The element
 * @return: The rank of the set at which the element is in
*/
int DisjointSet::rank(int id) {
    for (; this->set[id] >= 0; id = this->set[id]);
    return -this->set[id];
}

/**
 * METHOD: merge
 * Given 2 set representations, merging 2 sets into 1 such that the 
 * src set will be the subset of the dest set (retains the representation of set dest)
 * @param src: The set to join the dest set
 * @param dest: The set to be joined 
*/
void DisjointSet::merge(int src, int dest) {
    if (src == dest || this->set[src] >= 0 || this->set[dest] >= 0)
        return;

    this->set[dest] += this->set[src];
    this->set[src] = dest;
    --n_sets;
    return; 
}