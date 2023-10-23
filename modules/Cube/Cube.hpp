#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <vector>
#include <unordered_map>

#include "PublicTypes.hpp"
#include "Image.hpp"
#include "HashFunction.hpp"
#include "ImageDistance.hpp"

class Cube
{
private:
    int dimension;     // –k number of dimensions
    int maxCanditates; // -M maximum candidates
    int probes;        // -p probes
    int numNn;         // -Ν number of nearest Neighbors
    int w;
    int numBuckets;
    std::vector<std::vector<ImagePtr>> buckets;
    std::unordered_map<int, int> *map;
    std::vector<HashFunction> hash_functions;
    int hash(ImagePtr image);
    ImageDistance *distance;

public:
    Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, int numBuckets);
    ~Cube();
    void insert(ImagePtr image);
    std::vector<Neighbor> Approximate_kNN(ImagePtr query);
    std::vector<ImagePtr> Approximate_Range_Search(ImagePtr query, const double radius);
};

#endif
