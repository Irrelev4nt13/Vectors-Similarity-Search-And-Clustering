#include <vector>
#include <queue>
#include <tuple>

#include "Image.hpp"
#include "Utils.hpp"
#include "BruteForce.hpp"
#include "PublicTypes.hpp"

std::vector<Neighbor> BruteForce(const std::vector<ImagePtr> &images_input, const ImagePtr query, const int k)
{
    std::priority_queue<Neighbor, std::vector<Neighbor>, CompareTuple> nearestNeighbors;

    for (ImagePtr input : images_input)
    {
        double dist = EuclideanDistance(input->pixels, query->pixels);
        Neighbor new_tuple(input, dist);
        nearestNeighbors.push(new_tuple);

        if (nearestNeighbors.size() > k)
            nearestNeighbors.pop();
    }

    std::vector<Neighbor> KnearestNeighbors;
    while (!nearestNeighbors.empty())
    {
        KnearestNeighbors.insert(KnearestNeighbors.begin(), nearestNeighbors.top());
        nearestNeighbors.pop();
    }
    return KnearestNeighbors;
}