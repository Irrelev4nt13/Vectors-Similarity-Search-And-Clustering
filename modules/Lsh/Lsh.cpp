#include <iostream>
#include <queue>
#include <vector>

#include <Lsh.hpp>
#include <FileParser.hpp>

Lsh::Lsh(const std::vector<Image> &images, const int &numHashFuncs, const int &numHtables, const int &numNn, const double &radius, const int &w, const int &numBuckets)
    : numHashFuncs(numHashFuncs), numHtables(numHtables), numNn(numNn), radius(radius), w(w), numBuckets(numBuckets)
{
  int dimension = images.at(0).pixels.size();
  for (int i = 0; i < numHtables; i++)
  {
    hashtables.push_back(HashTable(numBuckets, AmplifiedHashFunction(w, numHashFuncs, dimension)));
    for (int j = 0; j < images.size(); j++)

      hashtables[i].insert(images[j]);
    // break;
  }
  // break;
  // std::cout << hashtables.size() << std::endl;
}

Lsh::~Lsh() {}

void Lsh::print_lsh()
{
  std::cout << numHashFuncs << std::endl;
  std::cout << numHtables << std::endl;
  std::cout << numNn << std::endl;
  std::cout << radius << std::endl;
}

class CompareTuple
{
public:
  bool operator()(const std::tuple<Image, double> &a, const std::tuple<Image, double> &b) const
  {
    // Compare based on the double value.
    return std::get<1>(a) < std::get<1>(b);
  }
};
std::vector<std::tuple<Image, double>> Lsh::Approximate_kNN(const Image &query)
{
  std::priority_queue<std::tuple<Image, double>, std::vector<std::tuple<Image, double>>, CompareTuple> nearestNeighbors;

  for (int i = 0; i < numHtables; i++)
  {
    const std::vector<Image> bucket = hashtables[i].get_bucket(query);

    for (const Image &input : bucket)
    {
      double dist = EuclideanDistance(input.pixels, query.pixels);
      std::tuple<Image, double> new_tuple(input, dist);
      nearestNeighbors.push(new_tuple);

      if (nearestNeighbors.size() > numNn)
        nearestNeighbors.pop();
    }
  }
  // Find the bucket that the query is in
  // loop through all it's element calculate distance with every one of them and add it in the priority queue

  std::vector<std::tuple<Image, double>> KnearestNeighbors;
  while (!nearestNeighbors.empty())
  {
    KnearestNeighbors.insert(KnearestNeighbors.begin(), nearestNeighbors.top());
    nearestNeighbors.pop();
  }
  return KnearestNeighbors;
}

std::vector<Image> Lsh::Approximate_Range_Search(const Image &query)
{
  std::vector<Image> RangeSearch;
  for (int i = 0; i < numHtables; i++)
  {
    const std::vector<Image> bucket = hashtables[i].get_bucket(query);

    for (const Image &input : bucket)
    {
      double dist = EuclideanDistance(input.pixels, query.pixels);
      if (dist >= 0 && dist < radius)
        RangeSearch.push_back(input);
    }
  }
  return RangeSearch;
}