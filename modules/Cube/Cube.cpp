#include <iostream>
#include <vector>

#include "Cube.hpp"
#include "HashTable.hpp"

Cube::Cube(const std::vector<ImagePtr> images, int w, int dimension, int maxCanditates, int probes, int numNn, double radius)
    : dimension(dimension), maxCanditates(maxCanditates), probes(probes), numNn(numNn), radius(radius)
{
    this->hashTable = new HashTable(dimension, AmplifiedHashFunction(w, dimension, dimension));

    for (int i = 0; i < images.size(); i++)
    {
        this->hashTable->insert(images[i]);
    }
}

Cube::~Cube()
{
    delete this->hashTable;
}

void Cube::print_cube()
{
    std::cout << dimension << std::endl;
    std::cout << maxCanditates << std::endl;
    std::cout << probes << std::endl;
    std::cout << numNn << std::endl;
    std::cout << radius << std::endl;
}