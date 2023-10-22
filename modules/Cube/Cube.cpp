#include <vector>
#include <queue>
#include <bitset>

#include "Utils.hpp"
#include "Cube.hpp"
#include "PublicTypes.hpp"
#include "HashFunction.hpp"

Cube::Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, int numBuckets)
    : dimension(dimension), maxCanditates(maxCanditates), probes(probes), numNn(numNn), w(w), numBuckets(numBuckets)
{
    std::normal_distribution<> standard_normal(0.0, 1.0);
    std::uniform_real_distribution<> uniform_real(0, w);

    for (int i = 0; i < dimension; i++)
    {
        std::vector<double> v;
        for (std::size_t j = 0; j < images[0]->pixels.size(); j++)
            v.push_back(standard_normal(RandGen()));
        hash_functions.push_back(HashFunction(w, uniform_real(RandGen()), v));
    }
    for (int i = 0; i < numBuckets; i++)
        buckets.push_back(std::vector<ImagePtr>());

    map = new std::unordered_map<int, int>[dimension];

    for (std::size_t i = 0; i < images.size(); i++)
        insert(images[i]);
}

int Cube::hash(ImagePtr image)
{
    std::uniform_int_distribution<> uniform_int(0, 1);
    std::string res = "";
    for (int i = 0; i < dimension; i++)
    {
        int hash = hash_functions[i].hash(image);
        if (map[i].find(hash) == map[i].end())
            map[i][hash] = uniform_int(RandGen());

        res += std::to_string(map[i][hash]);
    }
    return std::bitset<32>(res).to_ulong();
}

Cube::~Cube() { delete[] map; }

void Cube::insert(ImagePtr image) { buckets[hash(image)].push_back(image); }

std::vector<Neighbor> Cube::Approximate_kNN(ImagePtr query)
{
    std::priority_queue<Neighbor, std::vector<Neighbor>, CompareTuple> nearestNeighbors;
    int query_bucket = hash(query);
    int candidates = 0;
    std::vector<ImagePtr> bucket;
    for (int i = 0; i < probes + 1 && candidates < maxCanditates; i++)
    {
        if (i == 0)
        {
            bucket = buckets[query_bucket];
            for (ImagePtr input : bucket)
            {
                double dist = EuclideanDistance(input->pixels, query->pixels);
                nearestNeighbors.push(Neighbor(input, dist));
                if ((int)nearestNeighbors.size() > numNn)
                    nearestNeighbors.pop();
                if (++candidates == maxCanditates)
                    break;
            }
        }
        else
        {
            for (int j = 0; j < numBuckets && candidates < maxCanditates; j++)
            {
                if (HammingDistance(query_bucket, j) == i)
                {
                    bucket = buckets[j];
                    for (ImagePtr input : bucket)
                    {
                        double dist = EuclideanDistance(input->pixels, query->pixels);
                        nearestNeighbors.push(Neighbor(input, dist));
                        if ((int)nearestNeighbors.size() > numNn)
                            nearestNeighbors.pop();
                        if (++candidates == maxCanditates)
                            break;
                    }
                }
            }
        }
    }

    std::vector<Neighbor> KnearestNeighbors;
    while (!nearestNeighbors.empty())
    {
        KnearestNeighbors.insert(KnearestNeighbors.begin(), nearestNeighbors.top());
        nearestNeighbors.pop();
    }
    return KnearestNeighbors;
}
std::vector<ImagePtr> Cube::Approximate_Range_Search(ImagePtr query, const double radius)
{
    std::vector<ImagePtr> RangeSearch;

    int query_bucket = hash(query);
    int candidates = 0;

    std::vector<ImagePtr> bucket;
    for (int i = 0; i < probes + 1 && candidates < maxCanditates; i++)
    {
        if (i == 0)
        {
            bucket = buckets[query_bucket];
            for (ImagePtr input : bucket)
            {
                double dist = EuclideanDistance(input->pixels, query->pixels);
                if (dist <= radius)
                    RangeSearch.push_back(input);
                if (++candidates == maxCanditates)
                    break;
            }
        }
        else
        {
            for (int j = 0; j < numBuckets && candidates < maxCanditates; j++)
            {
                if (HammingDistance(query_bucket, j) == i)
                {
                    bucket = buckets[j];
                    for (ImagePtr input : bucket)
                    {
                        double dist = EuclideanDistance(input->pixels, query->pixels);
                        if (dist <= radius)
                            RangeSearch.push_back(input);
                        if (++candidates == maxCanditates)
                            break;
                    }
                }
            }
        }
    }
    return RangeSearch;
}