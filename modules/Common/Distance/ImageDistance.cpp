#include <iostream>
#include <vector>
#include <cmath>

#include "ImageDistance.hpp"

ImageDistance::ImageDistance(const std::string &metric)
    : metric(metric) {}

ImageDistance::~ImageDistance() {}

ImageDistance *ImageDistance::getInstance(const std::string &metric)
{
    if (!instance)
        instance = new ImageDistance(metric);
    return instance;
}

double ImageDistance::calculate(const ImagePtr &input, const ImagePtr &query)
{
    if (metric == "l2")
    {
        return EuclideanImageDistance(input, query);
    }
    else if (metric == "l1")
    {
        return ManhattanDistance(input, query);
    }

    std::cerr << "ImageDistance: unexpected error. Metric " << metric << " is invalid" << std::endl;
    exit(EXIT_FAILURE);
}

double ImageDistance::EuclideanImageDistance(const ImagePtr &first, const ImagePtr &second)
{
    double difference, result = 0.0;
    size_t limit = first->pixels.size();
    for (size_t i = 0; i < limit; i++)
    {
        difference = first->pixels[i] - second->pixels[i];
        result += difference * difference;
    }
    return sqrt(result);
}

double ImageDistance::ManhattanDistance(const ImagePtr &first, const ImagePtr &second)
{
    double result = 0;
    size_t limit = first->pixels.size();
    for (size_t i = 0; i < limit; i++)
        result += std::abs(first->pixels[i] - second->pixels[i]);
    return result;
}
