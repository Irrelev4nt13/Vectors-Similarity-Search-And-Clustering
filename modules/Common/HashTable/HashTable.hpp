#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

#include <vector>

#include "Image.hpp"
#include "PublicTypes.hpp"

class HashFunction
{
private:
    int w;
    float t;
    std::vector<double> v;

public:
    HashFunction(const int &w, const float &t, const std::vector<double> &v);
    ~HashFunction();

    int hash(ImagePtr image) const;
};

class AmpLsh : public GenericAmp
{
private:
    std::vector<int> r;
    std::vector<HashFunction> hash_functions;

public:
    AmpLsh(const int &w, const int &numHashFuncs, const int &dimension);
    ~AmpLsh();

    int hash(ImagePtr image) const;
};

template <typename T>
using Bucket = std::vector<T>;

class HashTable
{
private:
    int numBuckets;
    std::vector<Bucket<ImagePtr>> buckets;
    GenericAmp *hashmap;

public:
    HashTable(const int &numBuckets, GenericAmp *hash);
    ~HashTable();

    void insert(ImagePtr image);

    std::vector<ImagePtr> get_bucket(ImagePtr image);
};

#endif