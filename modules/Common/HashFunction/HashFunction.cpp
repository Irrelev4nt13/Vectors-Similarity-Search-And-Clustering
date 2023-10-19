
#include <iostream>
#include <vector>

#include "HashFunction.hpp"
#include "Utils.hpp"
#include "PublicTypes.hpp"

HashFunction::HashFunction(const int w, const float t, const std::vector<double> &v) : w(w), t(t), v(v) {}

HashFunction::~HashFunction() {}

int HashFunction::hash(ImagePtr image) const { return floor((DotProduct(v, image->pixels) + t) / w); }
