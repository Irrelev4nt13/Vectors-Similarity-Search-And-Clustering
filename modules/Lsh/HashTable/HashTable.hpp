#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

#include <vector>
#include <unordered_map>

#include "Image.hpp"
#include "HashFunction.hpp"
#include "PublicTypes.hpp"

class AmpLsh
{
private:
    std::vector<int> r;
    std::vector<HashFunction> hash_functions;

public:
    AmpLsh(int w, int numHashFuncs, int dimension);
    ~AmpLsh();

    int hash(ImagePtr image);
};

template <typename T>
using Bucket = std::vector<T>;

class HashTable
{
private:
    int numBuckets;
    std::vector<Bucket<ImagePtr>> buckets;
    AmpLsh hashmap;

public:
    HashTable(int numBuckets, const AmpLsh &hashmap);
    ~HashTable();

    void insert(ImagePtr image);

    std::vector<ImagePtr> get_bucket(ImagePtr image);
};

#endif