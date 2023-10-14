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
    Lsh(const std::vector<Image> &images, const int &numHashFuncs, const int &numHtables, const int &numNn, const double &radius, const int &w, const int &numBuckets);
    ~Lsh();
    std::vector<std::tuple<Image, double>> Approximate_kNN(const Image &query);
    std::vector<Image> Approximate_Range_Search(const Image &query);
};

#endif