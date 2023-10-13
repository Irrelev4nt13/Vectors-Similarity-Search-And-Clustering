#pragma once
#include <iostream>
#include <vector>
#include <queue>

#include <Image.hpp>
#include <Utils.hpp>

// Custom comparison function to sort the tuples by the double value.
class CompareTuple
{
public:
    bool operator()(const std::tuple<Image, double> &a, const std::tuple<Image, double> &b) const
    {
        // Compare based on the double value.
        return std::get<1>(a) < std::get<1>(b);
    }
};

std::vector<std::tuple<Image, double>> BruteForce(const std::vector<Image> &images_input, const Image &query, int k)
{
    std::priority_queue<std::tuple<Image, double>, std::vector<std::tuple<Image, double>>, CompareTuple> nearestNeighbors;

    for (const Image &input : images_input)
    {
        double dist = EuclideanDistance(input.pixels, query.pixels);
        std::tuple<Image, double> new_tuple(input, dist);
        nearestNeighbors.push(new_tuple);

        if (nearestNeighbors.size() > k)
            nearestNeighbors.pop();
    }

    std::vector<std::tuple<Image, double>> KnearestNeighbors;
    while (!nearestNeighbors.empty())
    {
        KnearestNeighbors.insert(KnearestNeighbors.begin(), nearestNeighbors.top());
        nearestNeighbors.pop();
    }
    return KnearestNeighbors;
}