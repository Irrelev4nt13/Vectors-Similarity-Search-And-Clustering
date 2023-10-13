#include <iostream>
#include <Lsh.hpp>
#include <FileParser.hpp>

Lsh::Lsh(const std::vector<Image> &images, const int &numHashFuncs, const int &numHtables, const int &numNn, const double &radius, const int &w, const int &numBuckets)
    : numHashFuncs(numHashFuncs), numHtables(numHtables), numNn(numNn), radius(radius), w(w), numBuckets(numBuckets)
{
  for (int i = 0; i < numHtables; i++)
    hashtables.push_back(HashTable(numBuckets, AmplifiedHashFunction(w, numHashFuncs, images.size())));
  std::cout << hashtables.size() << std::endl;
}

Lsh::~Lsh() {}

void Lsh::print_lsh()
{
  std::cout << numHashFuncs << std::endl;
  std::cout << numHtables << std::endl;
  std::cout << numNn << std::endl;
  std::cout << radius << std::endl;
}

void Lsh::Approximate_kNN() {}
void Lsh::Approximate_Range_Search() {}