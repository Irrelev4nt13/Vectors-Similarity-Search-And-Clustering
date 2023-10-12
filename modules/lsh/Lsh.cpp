#include <iostream>
#include <Lsh.hpp>

Lsh::Lsh(const int &numHashFuncs, const int &numHtables, const int &numNn, const double &radius)
    : numHashFuncs(numHashFuncs), numHtables(numHtables), numNn(numNn), radius(radius) {}

Lsh::~Lsh() {}

void Lsh::print_lsh()
{
  std::cout << numHashFuncs << std::endl;
  std::cout << numHtables << std::endl;
  std::cout << numNn << std::endl;
  std::cout << radius << std::endl;
}