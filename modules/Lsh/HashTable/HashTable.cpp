#include <vector>
#include <random>
#include <unordered_map>
#include <string>
#include <climits>
#include <cstdint>

#include "Utils.hpp"
#include "HashTable.hpp"

static const int64_t M = ((int64_t)(1) << 32) - 5;

AmpLsh::AmpLsh(int w, int numHashFuncs, int dimension)
{
    std::normal_distribution<> standard_normal(0.0, 1.0);
    std::uniform_real_distribution<> uniform_real(0, w);
    std::uniform_int_distribution<> uniform_int(0, INT32_MAX);

    for (int i = 0; i < numHashFuncs; i++)
    {
        r.push_back(uniform_int(RandGen()));

        std::vector<double> v;
        for (int j = 0; j < dimension; j++)
            v.push_back(standard_normal(RandGen()));
        hash_functions.push_back(HashFunction(w, uniform_real(RandGen()), v));
    }
}
AmpLsh::~AmpLsh() {}

int AmpLsh::hash(ImagePtr image)
{
    uint64_t hashval = 0;
    for (int i = 0, num_hashes = hash_functions.size(); i < num_hashes; i++)
        hashval += r[i] * hash_functions[i].hash(image);
    return Modulo(hashval, M);
}

HashTable::HashTable(int numBuckets, const AmpLsh &hash) : numBuckets(numBuckets), hashmap(hash)
{
    buckets.resize(numBuckets);
    for (int i = 0; i < numBuckets; i++)
    {
        std::vector<ImagePtr> new_bucket;
        buckets[i] = new_bucket;
    }
}

HashTable::~HashTable()
{
}

void HashTable::insert(ImagePtr image)
{
    buckets.at(Modulo(hashmap.hash(image), numBuckets)).push_back(image);
}

std::vector<ImagePtr> HashTable::get_bucket(ImagePtr image) { return buckets.at(Modulo(hashmap.hash(image), numBuckets)); }
