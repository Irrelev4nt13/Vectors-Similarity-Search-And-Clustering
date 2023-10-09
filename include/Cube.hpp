#pragma once

#include <iostream>

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
    Cube(const std::string &input_file,
         const std::string &query_file,
         const int &dimension,
         const int &max_candidates,
         const int &probes,
         const std::string &output_file,
         const int &num_of_nearest_neighbors,
         const double &radius);
    ~Cube();
    void print_cube()
    {
        std::cout << input_file << std::endl;
        std::cout << query_file << std::endl;
        std::cout << dimension << std::endl;
        std::cout << max_candidates << std::endl;
        std::cout << probes << std::endl;
        std::cout << output_file << std::endl;
        std::cout << num_of_nearest_neighbors << std::endl;
        std::cout << radius << std::endl;
    }
};