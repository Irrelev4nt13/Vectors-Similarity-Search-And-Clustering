#pragma once

#include <iostream>

class Lsh
{
private:
    int numHashFuncs; // –k number of hash functions
    int numHtables;   // -L number of hash tables
    int numNn;        // -Ν number of Nearest Neighbors
    double radius;    // -R radius

public:
    Lsh(const int &numHashFuncs, const int &numHtables, const int &numNn, const double &radius);
    ~Lsh();
    void print_lsh();
};