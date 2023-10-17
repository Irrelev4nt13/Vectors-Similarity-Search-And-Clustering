#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <iostream>
#include <vector>
#include <unordered_map>

#include "Table.hpp"
#include "PublicTypes.hpp"
#include "Image.hpp"

class Cube
{
private:
    int dimension;     // –k number of dimensions
    int maxCanditates; // -M maximum candidates
    int probes;        // -p probes
    int numNn;         // -Ν number of nearest Neighbors
    double radius;     // -R radius
    // HashTablee hashTable; // hypercube hash table
    // std::vector<CubeMap> cubeMaps; // map string hash values to {0, 1}^d
    int w;

public:
    Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, double radius);
    ~Cube();
    void print_cube();
    std::vector<std::tuple<Image *, double>> Approximate_kNN(Image *query);
    std::vector<Image *> Approximate_Range_Search(Image *query);
};

#endif
