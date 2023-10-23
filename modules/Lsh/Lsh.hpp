#ifndef LSH_HPP_
#define LSH_HPP_

#include <vector>


#include "Image.hpp"
#include "HashTable.hpp"
#include "ImageDistance.hpp"
class Lsh
{
private:
    int numHashFuncs;                  // –k number of hash functions
    int numHtables;                    // -L number of hash tables
    int numNn;                         // -Ν number of Nearest Neighbors
    int w;                             // w
    int numBuckets;                    // number of buckets
    std::vector<HashTable> hashtables; // hash tables
    ImageDistance *distance;

public:
    Lsh(const std::vector<ImagePtr> &images, int numHashFuncs, int numHtables, int numNn, int w, int numBuckets);
    ~Lsh();
    std::vector<Neighbor> Approximate_kNN(ImagePtr query);
    std::vector<ImagePtr> Approximate_Range_Search(ImagePtr query, const double radius);
};

#endif