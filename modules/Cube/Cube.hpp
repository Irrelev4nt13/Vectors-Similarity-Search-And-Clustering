#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <iostream>
#include <vector>

#include "PublicTypes.hpp"
#include "Image.hpp"
#include "HashTable.hpp"

class Cube
{
private:
    int dimension;       // –k number of dimensions
    int maxCanditates;   // -M maximum candidates
    int probes;          // -p probes
    int numNn;           // -Ν number of nearest Neighbors
    double radius;       // -R radius
    HashTable hashTable; // hypercube hash table
    int w;

public:
    Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, double radius, int numBuckets);
    ~Cube();
    void print_cube();
    std::vector<Neighbor> Approximate_kNN(Image *query);
    std::vector<ImagePtr> Approximate_Range_Search(Image *query);
};

#endif
