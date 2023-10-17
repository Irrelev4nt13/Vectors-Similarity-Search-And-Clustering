#include <iostream>
#include <vector>

#include <queue>

#include "Cube.hpp"
#include "PublicTypes.hpp"
#include "Table.hpp"

Cube::Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, double radius)
    : dimension(dimension), maxCanditates(maxCanditates), probes(probes), numNn(numNn), radius(radius), w(w)
//   hashTable(1, AmplifiedHashFunction(1, 1, 1))
//   hashTable(1 << dimension, AmplifiedHashFunction(w, dimension, images.at(0)->pixels.size()))
{
    std::cout << dimension << std::endl;
    // HashTablee(1 << dimension, AmplifiedHashFunction(w, dimension, images.at(0)->pixels.size()));
    // AmplifiedHashFunction temp(w, dimension, images.at(0)->pixels.size());
    // std::cout << (1 << dimension) << std::endl;
    // for (int i = 0; i < images.size(); i++)
    //     hashTable.insert(images[i]);
}

Cube::~Cube() {}

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
    std::priority_queue<std::tuple<Image *, double>, std::vector<std::tuple<Image *, double>>, CompareTuple> nearestNeighbors;

    // Do the search

    std::vector<std::tuple<Image *, double>> KnearestNeighbors;
    while (!nearestNeighbors.empty())
    {
        KnearestNeighbors.insert(KnearestNeighbors.begin(), nearestNeighbors.top());
        nearestNeighbors.pop();
    }
    return KnearestNeighbors;
}
std::vector<Image *> Cube::Approximate_Range_Search(ImagePtr query)
{
    std::vector<Image *> vec;
    return vec;
}