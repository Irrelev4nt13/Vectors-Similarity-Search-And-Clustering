#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <bitset>
#include <iomanip>

#include "Utils.hpp"
#include "Cube.hpp"
#include "PublicTypes.hpp"
#include "HashFunction.hpp"

Cube::Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, double radius, int numBuckets)
    : dimension(dimension), maxCanditates(maxCanditates), probes(probes), numNn(numNn), radius(radius), w(w), numBuckets(numBuckets)
{
    std::normal_distribution<> standard_normal(0.0, 1.0);
    std::uniform_real_distribution<> uniform_real(0, w);

    for (int i = 0; i < dimension; i++)
    {
        std::vector<double> v;
        for (int j = 0; j < images[0]->pixels.size(); j++)
            v.push_back(standard_normal(RandGen()));
        hash_functions.push_back(HashFunction(w, uniform_real(RandGen()), v));
    }
    for (int i = 0; i < numBuckets; i++)
        buckets.push_back(std::vector<ImagePtr>());

    map = new std::unordered_map<int, int>[dimension];
    for (int i = 0; i < images.size(); i++)
    {
        insert(images[i]);
    }
}

int Cube::hash(ImagePtr image)
{
    std::uniform_int_distribution<> uniform_int(0, 1);
    std::string res = "";
    for (int i = 0; i < dimension; i++)
    {
        int hash = hash_functions[i].hash(image);
        // std::cout << hash << " ";
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

    // std::cout << std::endl;
    // std::cout << std::endl;
    int query_bucket = hash(query);
    int candidates = 0;
    // std::cout << query_bucket << " " << std::bitset<32>(query_bucket).to_string() << std::endl;
    std::vector<ImagePtr> bucket = buckets[query_bucket];
    for (Image *input : bucket)
    {
        double dist = EuclideanDistance(input->pixels, query->pixels);
        // std::cout << dist << " ";
        Neighbor new_neighbor(input, dist);
        nearestNeighbors.push(new_neighbor);
        if (nearestNeighbors.size() > numNn)
            nearestNeighbors.pop();
        if (++candidates == maxCanditates)
            break;
    }
    if (candidates == maxCanditates)
    {
        std::vector<Neighbor> KnearestNeighbors;
        while (!nearestNeighbors.empty())
        {
            KnearestNeighbors.insert(KnearestNeighbors.begin(), nearestNeighbors.top());
            nearestNeighbors.pop();
        }
        return KnearestNeighbors;
    }
    for (int i = 1; i < probes + 1; i++)
    {

        for (int j = 0; j < numBuckets; j++)
        {
            if (HammingDistance(query_bucket, j) == i)
            {
                // std::cout << std::setw(6) << query_bucket << " and " << std::setw(6) << j << " has hamDistance: " << i
                //           << std::setw(6) << j << " bucket has: " << std::setw(6) << buckets[j].size() << " elements" << std::endl;
                bucket = buckets[j];
                for (Image *input : bucket)
                {
                    double dist = EuclideanDistance(input->pixels, query->pixels);
                    // std::cout << dist << " ";
                    Neighbor new_neighbor(input, dist);
                    nearestNeighbors.push(new_neighbor);
                    if (nearestNeighbors.size() > numNn)
                        nearestNeighbors.pop();
                    if (++candidates == maxCanditates)
                        break;
                }
            }
            if (candidates == maxCanditates)
                break;
        }
        if (candidates == maxCanditates)
            break;
        // if (i == 2)
        //     break;
    }
    // std::cout << std::endl;
    // std::cout << std::endl;
    // std::cout << (1 << 3) << std::endl;

    // Get buckets with ham distance + 1
    // for (int i = 0, candidates = 0; i <= probes && candidates < maxCanditates;)
    // {
    //     // if (i == 0)
    // }
    // Do the search
    // for (;;)
    // {
    //     // if ()
    // const std::vector<ImagePtr> bucket = buckets[query_bucket];
    // for (Image *input : bucket)
    // {
    //     double dist = EuclideanDistance(input->pixels, query->pixels);
    //     Neighbor new_neighbor(input, dist);
    //     nearestNeighbors.push(new_neighbor);

    //     if (nearestNeighbors.size() > numNn)
    //         nearestNeighbors.pop();
    // }
    //     if (maxCanditates)
    //         break;
    // }
    std::vector<Neighbor> KnearestNeighbors;
    while (!nearestNeighbors.empty())
    {
        KnearestNeighbors.insert(KnearestNeighbors.begin(), nearestNeighbors.top());
        nearestNeighbors.pop();
    }
    return KnearestNeighbors;
}
std::vector<ImagePtr> Cube::Approximate_Range_Search(ImagePtr query)
{
    std::vector<ImagePtr> RangeSearch;

    // std::cout << std::endl;
    // std::cout << std::endl;
    int query_bucket = hash(query);
    int candidates = 0;
    // std::cout << query_bucket << " " << std::bitset<32>(query_bucket).to_string() << std::endl;
    std::vector<ImagePtr> bucket = buckets[query_bucket];
    for (Image *input : bucket)
    {
        double dist = EuclideanDistance(input->pixels, query->pixels);
        if (dist <= radius)
            RangeSearch.push_back(input);
        if (++candidates == maxCanditates)
            break;
    }
    if (candidates == maxCanditates)
        return RangeSearch;

    for (int i = 1; i < probes + 1; i++)
    {

        for (int j = 0; j < numBuckets; j++)
        {
            if (HammingDistance(query_bucket, j) == i)
            {
                // std::cout << std::setw(6) << query_bucket << " and " << std::setw(6) << j << " has hamDistance: " << i
                //           << std::setw(6) << j << " bucket has: " << std::setw(6) << buckets[j].size() << " elements" << std::endl;
                bucket = buckets[j];
                for (Image *input : bucket)
                {
                    double dist = EuclideanDistance(input->pixels, query->pixels);
                    if (dist <= radius)
                        RangeSearch.push_back(input);
                    if (++candidates == maxCanditates)
                        break;
                }
            }
            if (candidates == maxCanditates)
                break;
        }
        if (candidates == maxCanditates)
            break;
        // if (i == 2)
        //     break;
    }
    return RangeSearch;
}