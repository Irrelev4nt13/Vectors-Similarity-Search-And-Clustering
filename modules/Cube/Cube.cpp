#include <iostream>
#include <Cube.hpp>

Cube::Cube(int dimension, int maxCanditates, int probes, int numNn, double radius)
    : dimension(dimension),
      maxCanditates(maxCanditates),
      probes(probes),
      numNn(numNn),
      radius(radius) {}

Cube::~Cube() {}

void Cube::print_cube()
{
    std::cout << dimension << std::endl;
    std::cout << maxCanditates << std::endl;
    std::cout << probes << std::endl;
    std::cout << numNn << std::endl;
    std::cout << radius << std::endl;
}