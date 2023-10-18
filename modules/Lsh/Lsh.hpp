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
    std::vector<HashTable> hashtables; // hash tables
    int w;
    int numBuckets;

public:
    Lsh(const std::vector<ImagePtr> &images, int numHashFuncs, int numHtables, int numNn, double radius, int w, int numBuckets);
    ~Lsh();
    std::vector<std::tuple<Image *, double>> Approximate_kNN(Image *query);
    std::vector<Image *> Approximate_Range_Search(Image *query);
};

#endif