#pragma once

#include <iostream>

class Cluster
{
private:
    // The arguments initialized with the default values
    std::string input_file = "";         // –i <input file>
    std::string configuration_file = ""; // –c <configuration file>
    std::string output_file = "";        // -ο <output file>
    bool complete = false;               // -complete <optional>
    std::string method = "";             // -m <method: Classic OR LSH or Hypercube>

public:
    void parse_args(const int argc, const char *argv[]);
};