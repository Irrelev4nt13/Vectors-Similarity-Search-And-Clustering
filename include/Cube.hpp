#pragma once

#include <iostream>

class CubeArgs
{
public:
    std::string input_file = "";
    std::string query_file = "";
    int dimension = 14;
    int max_candidates = 10;
    int probes = 2;
    std::string output_file = "";
    int num_of_nearest_neighbors = 1;
    double radius = 10000;
};
class Cube
{
private:
    // The arguments initialized with the default values
    std::string input_file;       // –d <input file>
    std::string query_file;       // –q <query file>
    int dimension;                // –k <int>
    int max_candidates;           // -M <int>
    int probes;                   // -probes <int>
    std::string output_file;      // -ο <output file>
    int num_of_nearest_neighbors; // -Ν <number of nearest>
    double radius;                // -R <radius>

public:
    Cube(const CubeArgs &args);
    ~Cube();
    void print_cube();
};