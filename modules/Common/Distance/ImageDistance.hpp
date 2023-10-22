#ifndef ImageDistance_HPP_
#define ImageDistance_HPP_

#include <iostream>
#include <vector>

#include "PublicTypes.hpp"

// Singleton class to configure distance metric
class ImageDistance
{
private:
    const std::string metric;

    static ImageDistance *instance;

    ImageDistance(const std::string &metric);

    double EuclideanImageDistance(const ImagePtr &first, const ImagePtr &second);

    double ManhattanDistance(const ImagePtr &first, const ImagePtr &second);

public:
    ~ImageDistance();
    static ImageDistance *getInstance(const std::string &metric);
    double calculate(const ImagePtr &input, const ImagePtr &query);

    // Delete copy/move constructors and assignment operators
    ImageDistance(const ImageDistance &) = delete;
    ImageDistance &operator=(const ImageDistance &) = delete;
    ImageDistance(ImageDistance &&) = delete;
    ImageDistance &operator=(ImageDistance &&) = delete;
};

// Initialize pointer
ImageDistance *ImageDistance::instance = 0;

#endif
