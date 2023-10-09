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

void split_cube_args(const int argc, const char *argv[],
                     std::string &input_file,
                     std::string &query_file,
                     int &dimension,
                     int &max_candidates,
                     int &probes,
                     std::string &output_file,
                     int &num_of_nearest_neighbors,
                     double &radius);

void split_cluster_args(const int argc, const char *argv[],
                        std::string &input_file,
                        std::string &configuration_file,
                        std::string &output_file,
                        bool &complete,
                        std::string &method);