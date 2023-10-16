#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <iostream>
#include <vector>
#include <unordered_map>

#include "HashTable.hpp"
#include "PublicTypes.hpp"
#include "Image.hpp"

class Cube
{
private:
    int dimension;                 // –k number of dimensions
    int maxCanditates;             // -M maximum candidates
    int probes;                    // -p probes
    int numNn;                     // -Ν number of nearest Neighbors
    double radius;                 // -R radius
    HashTable *hashTable;          // hypercube hash table
    std::vector<CubeMap> cubeMaps; // map string hash values to {0, 1}^d

public:
    Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, double radius);
    ~Cube();
    void print_cube();
    std::vector<Neighbor> Approximate_kNN(ImagePtr query);
    std::vector<ImagePtr> Approximate_Range_Search(ImagePtr query);
};

#endif
