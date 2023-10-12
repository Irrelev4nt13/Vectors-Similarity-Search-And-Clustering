#pragma once

#include <iostream>
#include <Lsh.hpp>
#include <Cube.hpp>
#include <Cluster.hpp>
#include <FileParser.hpp>
#include <vector>
#include <cstdint>

void split_cube_args(const int argc, const char *argv[], CubeArgs &args);

void split_cluster_args(const int argc, const char *argv[], ClusterArgs &args);

double DotProduct(const std::vector<double> &first, const std::vector<unsigned char> &second);

int64_t Modulo(int64_t first, int64_t second);

double EuclideanDistance(const std::vector<double> &first, const std::vector<unsigned char> &second);

double ManhattanDistance(const std::vector<double> &first, const std::vector<unsigned char> &second);