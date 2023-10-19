#ifndef PUBLIC_TYPES_HPP_
#define PUBLIC_TYPES_HPP_

#include <iostream>
#include <tuple>

#include "Image.hpp"

typedef Image *ImagePtr;

typedef std::tuple<ImagePtr, double> Neighbor;

class CompareTuple
{
public:
    bool operator()(const Neighbor &a, const Neighbor &b) const
    {
        // Compare based on the double value (distance).
        return std::get<1>(a) < std::get<1>(b);
    }
};

#endif