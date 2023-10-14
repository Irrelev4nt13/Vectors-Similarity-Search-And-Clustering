#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

#include <vector>

#include "Image.hpp"

#define MODULUS 4294967291 // This is a prime number (2^32 - 5)

class HashFunction
{
private:
    int w;
    float t;
    std::vector<double> v;

public:
    HashFunction(const int &w, const float &t, const std::vector<double> &v);
    ~HashFunction();

    int hash(Image *image) const;
};
class AmplifiedHashFunction
{
private:
    std::vector<int> r;
    std::vector<HashFunction> hash_functions;

public:
    AmplifiedHashFunction(const int &w, const int &numHashFuncs, const int &dimension);
    ~AmplifiedHashFunction();

    int hash(Image *image) const;
};

template <typename T>
using Bucket = std::vector<T>;

class HashTable
{
private:
    int numBuckets;
    std::vector<Bucket<Image *>> buckets;
    AmplifiedHashFunction hashamp;

public:
    HashTable(const int &numBuckets, const AmplifiedHashFunction &hash);
    ~HashTable();

    void insert(Image *image);

    std::vector<Image *> get_bucket(Image *image);
};

#endif