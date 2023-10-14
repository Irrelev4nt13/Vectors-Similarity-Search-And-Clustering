#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <random>
#include <cstdint>

// They need to be moved into another file with class based implementation
// void split_cube_args(const int argc, const char *argv[], CubeArgs &args);

// void split_cluster_args(const int argc, const char *argv[], ClusterArgs &args);

double DotProduct(const std::vector<double> &first, const std::vector<uint8_t> &second);

// template <typename T>
// uint Modulo(int first, int second);
int64_t Modulo(int64_t a, int64_t b);

double EuclideanDistance(const std::vector<unsigned char> &first, const std::vector<unsigned char> &second);

double ManhattanDistance(const std::vector<unsigned char> &first, const std::vector<unsigned char> &second);

std::mt19937 &RandGen();

#endif