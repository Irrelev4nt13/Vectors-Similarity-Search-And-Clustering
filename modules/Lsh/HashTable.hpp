#pragma once

#include <cmath>
#include <random>
#include <vector>

#include <Image.hpp>
#include <Utils.hpp>

#define MODULUS 4294967291 // This is a prime number (2^32 - 5)

class HashFunction
{
private:
    int w;
    int t;
    std::vector<double> v;

public:
    HashFunction(const int &w, const int &t, const std::vector<double> &v) : w(w), t(t), v(v) {}
    ~HashFunction() {}

    // int hash(const Image &image) const { return floor((DotProduct(v, image.pixels) + t) / w); }
};
class AmplifiedHashFunction
{
private:
    std::vector<int> r;
    std::vector<HashFunction> hash_functions;

public:
    AmplifiedHashFunction(const int &w, const int &numHashFuncs, const int &dimension)
    {
        std::vector<double> v;

        std::normal_distribution<> standard_normal(0.0, 1.0);
        std::uniform_real_distribution<> uniform_real(0, w);
        std::uniform_int_distribution<> uniform_int(0, INT32_MAX);

        // for (int i = 0; i < numHashFuncs; i++)
        // {
        //     r.push_back(uniform_int(RandGen()));

        //     for (int i = 0; i < dimension; i++)
        //         v.push_back(standard_normal(RandGen()));

        //     hash_functions.push_back(HashFunction(w, uniform_real(RandGen()), v));
        // }
    }
    ~AmplifiedHashFunction() {}

    // inline int hash(const Image &image) const
    // {
    //     int64_t hashval = 0;

    //     // Uses the property: (a + b) mod M = ((a mod M) + (b mod M)) mod M
    //     for (int i = 0, num_hashes = hash_functions.size(); i < num_hashes; i++)
    //         hashval = Modulo(Modulo(hashval, MODULUS) + Modulo(r[i] * hash_functions[i].hash(image), MODULUS), MODULUS);

    //     return hashval;
    // }
};

template <typename T>
using Bucket = std::vector<T>;

class HashTable
{
private:
    int numBuckets;
    std::vector<Bucket<Image>> buckets;
    AmplifiedHashFunction hash;

public:
    HashTable(const int &numBuckets, const AmplifiedHashFunction &hash) : numBuckets(numBuckets), hash(hash)
    {
        for (int i = 0; i < numBuckets; i++)
        {
            std::vector<Image> new_bucket;
            buckets.push_back(new_bucket);
        }
        std::cout << buckets.size() << std::endl;
    }
    ~HashTable() {}
    void insert() {}
    // int64_t GetHashVal(const Image *) {}
};
