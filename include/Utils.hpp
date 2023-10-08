#pragma once

#include <iostream>

void split_lsh_args(const int argc, const char *argv[],
                    std::string &input_file,
                    std::string &query_file,
                    int &num_of_hash_functions,
                    int &num_of_hash_tables,
                    std::string &output_file,
                    int &num_of_nearest_neighbors,
                    double &radius);
