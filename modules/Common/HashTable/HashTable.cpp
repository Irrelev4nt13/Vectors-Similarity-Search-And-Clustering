#include <vector>
#include <random>
#include <unordered_map>
#include <string>
#include <climits>
#include <cstdint>

#include "Utils.hpp"
#include "HashTable.hpp"

static const int64_t M = ((int64_t)(1) << 32) - 5;

HashFunction::HashFunction(const int &w, const float &t, const std::vector<double> &v) : w(w), t(t), v(v) {}

HashFunction::~HashFunction() {}

int HashFunction::hash(ImagePtr image) const { return floor((DotProduct(v, image->pixels) + t) / w); }

AmpLsh::AmpLsh(const int &w, const int &numHashFuncs, const int &dimension)
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
    uint hashval = 0;
    for (int i = 0, num_hashes = hash_functions.size(); i < num_hashes; i++)
        hashval += r[i] * hash_functions[i].hash(image);
    return Modulo(hashval, M);
}

AmpCube::AmpCube(int w, int numHashFuncs, int dimension)
{
    std::normal_distribution<> standard_normal(0.0, 1.0);
    std::uniform_real_distribution<> uniform_real(0, w);

    cubeMaps.resize(numHashFuncs);

    for (int i = 0; i < numHashFuncs; i++)
    {
        std::vector<double> v;
        for (int j = 0; j < dimension; j++)
            v.push_back(standard_normal(RandGen()));
        hash_functions.push_back(HashFunction(w, uniform_real(RandGen()), v));

        cubeMaps.push_back(std::unordered_map<int, int>());
    }
}

AmpCube::~AmpCube() {}

int AmpCube::hash(ImagePtr image)
{
    std::string bits = "";
    std::uniform_int_distribution<> uniform_int(0, 1);

    for (int i = 0; i < hash_functions.size(); i++)
    {
        int val_to_map = hash_functions[i].hash(image);

        if (cubeMaps[i].find(val_to_map) == cubeMaps[i].end())
            cubeMaps[i][val_to_map] = uniform_int(RandGen());

        bits += std::to_string(cubeMaps[i][val_to_map]);
    }
    return std::stoll(bits);
}

HashTable::HashTable(const int &numBuckets, GenericAmp *hash) : numBuckets(numBuckets), hashmap(hash)
{
    for (int i = 0; i < numBuckets; i++)
    {
        std::vector<ImagePtr> new_bucket;
        buckets.push_back(new_bucket);
    }
}

HashTable::~HashTable()
{
    delete hashmap;
}

void HashTable::insert(ImagePtr image) { buckets.at(Modulo(hashmap->hash(image), numBuckets)).push_back(image); }

std::vector<ImagePtr> HashTable::get_bucket(ImagePtr image) { return buckets.at(Modulo(hashmap->hash(image), numBuckets)); }
