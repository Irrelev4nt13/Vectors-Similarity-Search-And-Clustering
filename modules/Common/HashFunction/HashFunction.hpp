#ifndef HASH_FUNCTION_HPP_
#define HASH_FUNCTION_HPP_

#include <iostream>
#include <vector>
#include "PublicTypes.hpp"

class HashFunction
{
private:
    int w;
    double t;
    std::vector<double> v;

public:
    HashFunction(int w, double t, const std::vector<double> &v);
    ~HashFunction();

    uint64_t hash(ImagePtr image) const;
};

#endif
