#pragma once

#include <iostream>

class LshArgs
{
public:
    std::string input_file = "";
    std::string query_file = "";
    std::string output_file = "";
    int num_of_hash_functions = 4;
    int num_of_hash_tables = 5;
    int num_of_nearest_neighbors = 1;
    double radius = 10000;
};

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
    Lsh(const LshArgs &args);
    ~Lsh();
    void print_lsh();
};