#ifndef HASH_FUNCTION_HPP_
#define HASH_FUNCTION_HPP_

#include <iostream>
#include <vector>
#include "PublicTypes.hpp"

class HashFunction
{
private:
    int w;
    float t;
    std::vector<double> v;

public:
    HashFunction(const int w, const float t, const std::vector<double> &v);
    ~HashFunction();

    int hash(ImagePtr image) const;
};

#endif
