#pragma once

#include <iostream>

class Lsh
{
private:
    // The command line arguments
    std::string input_file;       // –d <input file>
    std::string query_file;       // –q <query file>
    int num_of_hash_functions;    // –k <int>
    int num_of_hash_tables;       // -L <int>
    std::string output_file;      // -ο <output file>
    int num_of_nearest_neighbors; // -Ν <number of nearest>
    double radius;                // -R <radius>

public:
    Lsh(const std::string &input_file,
        const std::string &query_file,
        const int &num_of_hash_functions,
        const int &num_of_hash_tables,
        const std::string &output_file,
        const int &num_of_nearest_neighbors,
        const double &radius);
    ~Lsh();
    void print_lsh()
    {
        std::cout << input_file << std::endl;
        std::cout << query_file << std::endl;
        std::cout << num_of_hash_functions << std::endl;
        std::cout << num_of_hash_tables << std::endl;
        std::cout << output_file << std::endl;
        std::cout << num_of_nearest_neighbors << std::endl;
        std::cout << radius << std::endl;
    }
};