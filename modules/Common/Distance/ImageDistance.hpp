#ifndef ImageDistance_HPP_
#define ImageDistance_HPP_

#include <iostream>
#include <vector>

#include "PublicTypes.hpp"

// Singleton class to configure distance metric
class ImageDistance
{
private:
    static DistanceMetric metric;

    static ImageDistance *instance;

    static bool isMetricSet;

    ImageDistance();

    double EuclideanImageDistance(const ImagePtr &first, const ImagePtr &second);

    double ManhattanDistance(const ImagePtr &first, const ImagePtr &second);

public:
    ~ImageDistance();
    static void setMetric(DistanceMetric metric);
    static ImageDistance *getInstance();
    double calculate(const ImagePtr &input, const ImagePtr &query);

    // Delete copy/move constructors and assignment operators
    ImageDistance(const ImageDistance &) = delete;
    ImageDistance &operator=(const ImageDistance &) = delete;
    ImageDistance(ImageDistance &&) = delete;
    ImageDistance &operator=(ImageDistance &&) = delete;
};

#endif
