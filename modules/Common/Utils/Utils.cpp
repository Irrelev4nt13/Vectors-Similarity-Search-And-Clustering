#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <cstdint>
#include <cmath>

#include <Utils.hpp>

void split_cube_args(const int argc, const char *argv[], CubeArgs &args)
{
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-d"))
            args.input_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-q"))
            args.query_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-k"))
            args.dimension = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-M"))
            args.max_candidates = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-probes"))
            args.probes = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-o"))
            args.output_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-N"))
            args.num_of_nearest_neighbors = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-R"))
            args.radius = atof(argv[i + 1]);
    }
}

void split_cluster_args(const int argc, const char *argv[], ClusterArgs &args)
{
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-i"))
            args.input_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-c"))
            args.configuration_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-o"))
            args.output_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-complete"))
            args.complete = true;
        else if (!strcmp(argv[i], "-m"))
            args.method = std::string(argv[i + 1]);
    }
}

double DotProduct(const std::vector<double> &first, const std::vector<unsigned char> &second)
{
    double sum = 0;
    int limit = first.size();
    for (int i = 0; i < limit; i++)
        sum += first[i] + second[i];
    return sum;
}

template <typename T>
uint Modulo(T first, T second) { return static_cast<uint>(first % second); }

double EuclideanDistance(const std::vector<unsigned char> &first, const std::vector<unsigned char> &second)
{
    double result = 0;
    int limit = first.size();
    for (int i = 0; i < limit; i++)
        result += pow((first[i] - second[i]), 2);
    return sqrt(result);
}

double ManhattanDistance(const std::vector<unsigned char> &first, const std::vector<unsigned char> &second)
{
    double result = 0;
    int limit = first.size();
    for (int i = 0; i < limit; i++)
        result += std::abs(first[i] - second[i]);
    return result;
}
