#include <vector>
#include <random>
#include <climits>
#include <cstdint>

#include "Utils.hpp"
#include "HashTable.hpp"

HashFunction::HashFunction(const int &w, const float &t, const std::vector<double> &v) : w(w), t(t), v(v) {}

HashFunction::~HashFunction() {}

int HashFunction::hash(const Image &image) const { return floor((DotProduct(v, image.pixels) + t) / w); }

AmplifiedHashFunction::AmplifiedHashFunction(const int &w, const int &numHashFuncs, const int &dimension)
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
AmplifiedHashFunction::~AmplifiedHashFunction() {}

int AmplifiedHashFunction::hash(const Image &image) const
{
    uint hashval = 0;
    for (int i = 0, num_hashes = hash_functions.size(); i < num_hashes; i++)
        hashval = Modulo(Modulo(hashval, MODULUS) + Modulo(r[i] * hash_functions[i].hash(image), MODULUS), MODULUS);
    return hashval;
}

HashTable::HashTable(const int &numBuckets, const AmplifiedHashFunction &hash) : numBuckets(numBuckets), hashamp(hash)
{
    for (int i = 0; i < numBuckets; i++)
    {
        std::vector<Image> new_bucket;
        buckets.push_back(new_bucket);
    }
}

HashTable::~HashTable() {}

void HashTable::insert(const Image &image) { buckets.at(Modulo(hashamp.hash(image), numBuckets)).push_back(image); }

std::vector<Image> HashTable::get_bucket(const Image &image) { return buckets.at(Modulo(hashamp.hash(image), numBuckets)); }
