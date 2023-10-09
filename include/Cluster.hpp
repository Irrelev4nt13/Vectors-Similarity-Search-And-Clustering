#pragma once

#include <iostream>
#include <iomanip>
class Cluster
{
private:
    // The arguments initialized with the default values
    std::string input_file;         // –i <input file>
    std::string configuration_file; // –c <configuration file>
    std::string output_file;        // -ο <output file>
    bool complete;                  // -complete <optional>
    std::string method;             // -m <method: Classic OR LSH or Hypercube>

public:
    Cluster(const std::string &input_file,
            const std::string &configuration_file,
            const std::string &output_file,
            const bool &complete,
            const std::string &method);
    ~Cluster();
    void print_cluster()
    {
        std::cout << input_file << std::endl;
        std::cout << configuration_file << std::endl;
        std::cout << output_file << std::endl;
        std::cout << std::boolalpha;
        std::cout << complete << std::endl;
        std::cout << method << std::endl;
    }
};