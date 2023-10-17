#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <vector>
#include <random>
#include <climits>
#include <string>
#include <cstdint>
#include <unordered_map>

#include "Utils.hpp"
#include "Image.hpp"

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

    // int64_t hash(Image *image) const { return floor((DotProduct(v, image->pixels) + t) / w); }
};
class AmplifiedHashFunction
{
private:
    std::vector<std::unordered_map<int64_t, int>> mapp_vals;
    std::vector<HashFunction> hash_functions;

public:
    AmplifiedHashFunction(const int &w, const int &numHashFuncs, const int &dimension)
    {
        // std::normal_distribution<> standard_normal(0.0, 1.0);
        // std::uniform_real_distribution<> uniform_real(0, w);
        // for (int i = 0; i < numHashFuncs; i++)
        // {
        // std::vector<double> v;
        // for (int j = 0; j < dimension; j++)
        //     v.push_back(standard_normal(RandGen()));
        // hash_functions.push_back(HashFunction(w, uniform_real(RandGen()), v));
        // mapp_vals.push_back(std::unordered_map<int64_t, int>());
        // }
    }
    ~AmplifiedHashFunction() {}

    // int64_t hash(Image *image)
    // {
    //     std::string concat_hashes = "";
    //     std::uniform_int_distribution<> uniform_int(0, 1);

    //     // The {0,1} labeling is local for each different LSH hash function
    //     for (int i = 0, num_hashes = hash_functions.size(); i < num_hashes; i++)
    //     {
    //         int64_t hash_value = hash_functions[i].hash(image);

    //         if (mapp_vals[i].find(hash_value) == mapp_vals[i].end())
    //         {
    //             mapp_vals[i][hash_value] = uniform_int(RandGen());
    //         }

    //         concat_hashes += std::to_string(mapp_vals[i][hash_value]);
    //     }

    //     // long long type is guaranteed to have a size of at least 64 bits
    //     return std::stoll(concat_hashes, 0, 2);
    // }
};

template <typename T>
using Bucket = std::vector<T>;

class HashTablee
{
private:
    int64_t numBuckets;
    std::vector<Bucket<Image *>> buckets;
    AmplifiedHashFunction hashamp;

public:
    HashTablee(const int64_t &numBuckets, const AmplifiedHashFunction &hash) : numBuckets(numBuckets), hashamp(hash)
    {
        // for (int i = 0; i < numBuckets; i++)
        // {
        //     std::vector<Image *> new_bucket;
        //     buckets.push_back(new_bucket);
        // }
    }
    ~HashTablee() {}

    // void insert(Image *image)
    // {
    //     // if (image->id == 53843)
    //     //     std::cout << "True bucket at: " << static_cast<int>(Modulo(hashamp.hash(image), numBuckets)) << std::endl;
    //     buckets.at(Modulo(hashamp.hash(image), numBuckets)).push_back(image);
    // }

    // std::vector<Image *> get_bucket(Image *image)
    // {
    //     // std::cout << "Aprox bucket at: " << static_cast<int>(Modulo(hashamp.hash(image), numBuckets)) << std::endl;

    //     return buckets.at(Modulo(hashamp.hash(image), numBuckets));
    // }
};

#endif