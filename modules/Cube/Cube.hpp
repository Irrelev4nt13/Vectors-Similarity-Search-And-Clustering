#ifndef CUBE_HPP_
#define CUBE_HPP_

#include <iostream>

class Cube
{
private:
    int dimension;     // –k number of dimensions
    int maxCanditates; // -M maximum candidates
    int probes;        // -p probes
    int numNn;         // -Ν number of nearest Neighbors
    double radius;     // -R radius

public:
    Cube(int dimension, int maxCanditates, int probes, int numNn, double radius);
    ~Cube();
    void print_cube();
};

#endif
