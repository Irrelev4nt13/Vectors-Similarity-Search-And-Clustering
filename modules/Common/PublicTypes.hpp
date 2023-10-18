#ifndef PUBLIC_TYPES_HPP_
#define PUBLIC_TYPES_HPP_

#include <iostream>
#include <tuple>

#include "Image.hpp"

typedef Image *ImagePtr;

typedef std::tuple<ImagePtr, double> Neighbor;

class GenericAmp
{
public:
    virtual int hash(ImagePtr image) = 0;
};

class CompareTuple
{
public:
    bool operator()(const std::tuple<ImagePtr, double> &a, const std::tuple<ImagePtr, double> &b) const
    {
        // Compare based on the double value.
        return std::get<1>(a) < std::get<1>(b);
    }
};

#endif