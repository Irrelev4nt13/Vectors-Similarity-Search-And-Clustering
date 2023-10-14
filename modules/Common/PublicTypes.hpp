#ifndef PUBLIC_TYPES_HPP_
#define PUBLIC_TYPES_HPP_

#include <iostream>

#include "Image.hpp"

// definitions of public common types used across all modules

typedef Image *ImagePtr;

typedef std::tuple<ImagePtr, double> Neighbor;

#endif
