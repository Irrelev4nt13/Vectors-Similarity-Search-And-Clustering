#pragma once

#include <iostream>

class Cube
{
private:
    // The arguments initialized with the default values
    std::string input_file = "";      // –d <input file>
    std::string query_file = "";      // –q <query file>
    int dimension = 14;               // –k <int>
    int max_candidates = 10;          // -M <int>
    int probes = 2;                   // -probes <int>
    std::string output_file = "";     // -ο <output file>
    int num_of_nearest_neighbors = 1; // -Ν <number of nearest>
    double radius = 10000;            // -R <radius>

public:
    void parse_args(const int argc, const char *argv[]);
};