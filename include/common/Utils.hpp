#pragma once

#include <iostream>
#include <Lsh.hpp>
#include <Cube.hpp>
#include <Cluster.hpp>
#include <Data.hpp>
#include <vector>

void split_lsh_args(const int argc, const char *argv[], LshArgs &args);

void split_cube_args(const int argc, const char *argv[], CubeArgs &args);

void split_cluster_args(const int argc, const char *argv[], ClusterArgs &args);

void parseInputFile(const std::string &inputFile, Metadata &metadata, std::vector<std::vector<char>> &images);