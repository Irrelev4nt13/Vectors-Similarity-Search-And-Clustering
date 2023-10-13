#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <Lsh.hpp>
#include <Cube.hpp>
#include <Cluster.hpp>
#include <FileParser.hpp>

void split_cube_args(const int argc, const char *argv[], CubeArgs &args);

void split_cluster_args(const int argc, const char *argv[], ClusterArgs &args);

double DotProduct(const std::vector<double> &first, const std::vector<uint> &second);

template <typename T>
uint Modulo(T first, T second);

double EuclideanDistance(const std::vector<unsigned char> &first, const std::vector<unsigned char> &second);

double ManhattanDistance(const std::vector<unsigned char> &first, const std::vector<unsigned char> &second);

std::mt19937 &RandGen();