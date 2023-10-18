#include <iostream>
#include <vector>
#include <queue>

#include "Utils.hpp"
#include "Cube.hpp"
#include "PublicTypes.hpp"
#include "HashTable.hpp"

Cube::Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, double radius, int numBuckets)
    : dimension(dimension), maxCanditates(maxCanditates), probes(probes), numNn(numNn), radius(radius), w(w)
{
    //   hashTable(numBuckets, AmpLsh(w, dimension, images[0]->pixels.size()))
    // for (int i = 0; i < images.size(); i++)
    //     hashTable.insert(images[i]);
}

Cube::~Cube()
{
}

void Cube::print_cube()
{
    std::cout << dimension << std::endl;
    std::cout << maxCanditates << std::endl;
    std::cout << probes << std::endl;
    std::cout << numNn << std::endl;
    std::cout << radius << std::endl;
}

std::vector<Neighbor> Cube::Approximate_kNN(ImagePtr query)
{
    std::priority_queue<Neighbor, std::vector<Neighbor>, CompareTuple> nearestNeighbors;

    // Do the search
    // for (;;)
    // {
    //     // if ()
    //     const std::vector<ImagePtr> bucket = hashTable.get_bucket(query);
    //     for (Image *input : bucket)
    //     {
    //         double dist = EuclideanDistance(input->pixels, query->pixels);
    //         Neighbor new_neighbor(input, dist);
    //         nearestNeighbors.push(new_neighbor);

    //         if (nearestNeighbors.size() > numNn)
    //             nearestNeighbors.pop();
    //     }
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
    std::vector<ImagePtr> vec;
    return vec;
}