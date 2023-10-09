#pragma once

#include <iostream>
#include <iomanip>

class ClusterArgs
{
public:
    std::string input_file = "";
    std::string configuration_file = "";
    std::string output_file = "";
    bool complete = false;
    std::string method = "";
};
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
    Cluster(const ClusterArgs &args);
    ~Cluster();
    void print_cluster();
};