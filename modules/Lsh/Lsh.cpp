#include <vector>
#include <queue>
#include <tuple>

#include "Image.hpp"
#include "Utils.hpp"
#include "HashTable.hpp"
#include "Lsh.hpp"
#include "PublicTypes.hpp"

Lsh::Lsh(const std::vector<ImagePtr> &images, int numHashFuncs, int numHtables, int numNn, double radius, int w, int numBuckets)
    : numHashFuncs(numHashFuncs), numHtables(numHtables), numNn(numNn), radius(radius), w(w), numBuckets(numBuckets)
{
  int dimension = images.at(0)->pixels.size();
  for (int i = 0; i < numHtables; i++)
  {
    hashtables.push_back(HashTable(numBuckets, AmpLsh(w, numHashFuncs, dimension)));
    for (int j = 0; j < images.size(); j++)

      hashtables[i].insert(images[j]);
  }
}

Lsh::~Lsh() {}

std::vector<Neighbor> Lsh::Approximate_kNN(ImagePtr query)
{
  std::priority_queue<Neighbor, std::vector<Neighbor>, CompareTuple> nearestNeighbors;

  for (int i = 0; i < numHtables; i++)
  {
    const std::vector<ImagePtr> bucket = hashtables[i].get_bucket(query);
    for (ImagePtr input : bucket)
    {
      double dist = EuclideanDistance(input->pixels, query->pixels);
      Neighbor new_tuple(input, dist);
      nearestNeighbors.push(new_tuple);

      if (nearestNeighbors.size() > numNn)
        nearestNeighbors.pop();
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

std::vector<ImagePtr> Lsh::Approximate_Range_Search(ImagePtr query)
{
  std::vector<ImagePtr> RangeSearch;
  for (int i = 0; i < numHtables; i++)
  {
    const std::vector<ImagePtr> bucket = hashtables[i].get_bucket(query);

    for (ImagePtr input : bucket)
    {
      double dist = EuclideanDistance(input->pixels, query->pixels);
      if (dist >= 0 && dist < radius)
        RangeSearch.push_back(input);
    }
  }
  return RangeSearch;
}