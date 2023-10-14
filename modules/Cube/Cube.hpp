#pragma once

#include <iostream>

class Cube
{
private:
    // The arguments initialized with the default values
    // std::string input_file;       // –d <input file>
    // std::string query_file;       // –q <query file>
    int dimension;     // –k <int>
    int maxCanditates; // -M <int>
    int probes;        // -probes <int>
    // std::string output_file;      // -ο <output file>
    int numNn;     // -Ν <number of nearest>
    double radius; // -R <radius>

public:
    Cube(int dimension, int maxCanditates, int probes, int numNn, double radius);
    ~Cube();
    void print_cube();
};