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
    float t;
    std::vector<double> v;

public:
    HashFunction(const int &w, const float &t, const std::vector<double> &v) : w(w), t(t), v(v) {}
    ~HashFunction() {}

    int hash(const Image &image) const { return floor((DotProduct(v, image.pixels) + t) / w); }
};
class AmplifiedHashFunction
{
private:
    std::vector<int> r;
    std::vector<HashFunction> hash_functions;

public:
    AmplifiedHashFunction(const int &w, const int &numHashFuncs, const int &dimension)
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
            // std::cout << dimension << std::endl;
            // std::cout << "Size v:\t" << (int)v.size() << std::endl;
            // std::cout << standard_normal(RandGen()) << std::endl;
            hash_functions.push_back(HashFunction(w, uniform_real(RandGen()), v));
        }
    }
    ~AmplifiedHashFunction() {}

    inline int hash(const Image &image) const
    {
        uint hashval = 0;

        // Uses the property: (a + b) mod M = ((a mod M) + (b mod M)) mod M
        // hashval = hash_functions[0].hash(image);
        for (int i = 0, num_hashes = hash_functions.size(); i < num_hashes; i++)
            hashval = Modulo(Modulo(hashval, MODULUS) + Modulo(r[i] * hash_functions[i].hash(image), MODULUS), MODULUS);

        return hashval;
    }
};

template <typename T>
using Bucket = std::vector<T>;

class HashTable
{
private:
    int numBuckets;
    std::vector<Bucket<Image>> buckets;
    AmplifiedHashFunction hashamp;

public:
    HashTable(const int &numBuckets, const AmplifiedHashFunction &hash) : numBuckets(numBuckets), hashamp(hash)
    {
        for (int i = 0; i < numBuckets; i++)
        {
            std::vector<Image> new_bucket;
            buckets.push_back(new_bucket);
        }
        // std::cout << buckets.size() << std::endl;
    }
    ~HashTable() {}
    void insert(const Image &image)
    {
        // std::cout << hashamp.hash(image) % numBuckets << std::endl;
        // int val = hashamp.hash(image);
        buckets.at(Modulo(hashamp.hash(image), numBuckets)).push_back(image);
    }
    std::vector<Image> get_bucket(const Image &image) { return buckets.at(Modulo(hashamp.hash(image), numBuckets)); }
    // uint hash(const Image &image) { return hashamp.hash() }
    // int64_t GetHashVal(const Image *) {}
};
