#include <vector>
#include <queue>
#include <tuple>

#include "Image.hpp"
#include "Utils.hpp"
#include "HashTable.hpp"
#include "Lsh.hpp"

Lsh::Lsh(const std::vector<Image *> &images, const int &numHashFuncs, const int &numHtables, const int &numNn, const double &radius, const int &w, const int &numBuckets)
    : numHashFuncs(numHashFuncs), numHtables(numHtables), numNn(numNn), radius(radius), w(w), numBuckets(numBuckets)
{
  int dimension = images.at(0)->pixels.size();
  for (int i = 0; i < numHtables; i++)
  {
    hashtables.push_back(HashTable(numBuckets, AmplifiedHashFunction(w, numHashFuncs, dimension)));
    for (int j = 0; j < images.size(); j++)

      hashtables[i].insert(images[j]);
  }
}

Lsh::~Lsh() {}

class CompareTuple
{
public:
  bool operator()(const std::tuple<Image *, double> &a, const std::tuple<Image *, double> &b) const
  {
    // Compare based on the double value.
    return std::get<1>(a) < std::get<1>(b);
  }
};
std::vector<std::tuple<Image *, double>> Lsh::Approximate_kNN(Image *query)
{
  std::priority_queue<std::tuple<Image *, double>, std::vector<std::tuple<Image *, double>>, CompareTuple> nearestNeighbors;

  for (int i = 0; i < numHtables; i++)
  {
    const std::vector<Image *> bucket = hashtables[i].get_bucket(query);

    for (Image *input : bucket)
    {
      double dist = EuclideanDistance(input->pixels, query->pixels);
      std::tuple<Image *, double> new_tuple(input, dist);
      nearestNeighbors.push(new_tuple);

      if (nearestNeighbors.size() > numNn)
        nearestNeighbors.pop();
    }
  }

  std::vector<std::tuple<Image *, double>> KnearestNeighbors;
  while (!nearestNeighbors.empty())
  {
    KnearestNeighbors.insert(KnearestNeighbors.begin(), nearestNeighbors.top());
    nearestNeighbors.pop();
  }
  return KnearestNeighbors;
}

std::vector<Image *> Lsh::Approximate_Range_Search(Image *query)
{
  std::vector<Image *> RangeSearch;
  for (int i = 0; i < numHtables; i++)
  {
    const std::vector<Image *> bucket = hashtables[i].get_bucket(query);

    for (Image *input : bucket)
    {
      double dist = EuclideanDistance(input->pixels, query->pixels);
      if (dist >= 0 && dist < radius)
        RangeSearch.push_back(input);
    }
  }
  return RangeSearch;
}