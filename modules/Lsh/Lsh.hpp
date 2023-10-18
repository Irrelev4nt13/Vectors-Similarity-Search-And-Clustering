#ifndef LSH_HPP_
#define LSH_HPP_

#include <vector>
#include <tuple>

#include "Image.hpp"
#include "HashTable.hpp"
class Lsh
{
private:
    int numHashFuncs;                  // –k number of hash functions
    int numHtables;                    // -L number of hash tables
    int numNn;                         // -Ν number of Nearest Neighbors
    double radius;                     // -R radius
    int w;                             // window
    int numBuckets;                    // number of buckets
    std::vector<HashTable> hashtables; // hash tables

public:
    Lsh(const std::vector<ImagePtr> &images, int numHashFuncs, int numHtables, int numNn, double radius, int w, int numBuckets);
    ~Lsh();
    std::vector<Neighbor> Approximate_kNN(ImagePtr query);
    std::vector<ImagePtr> Approximate_Range_Search(ImagePtr query);
};

#endif