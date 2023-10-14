#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <random>
#include <cstdint>

// They need to be moved into another file with class based implementation
// void split_cube_args(const int argc, const char *argv[], CubeArgs &args);

// void split_cluster_args(const int argc, const char *argv[], ClusterArgs &args);

template <typename T, typename U>
double DotProduct(const std::vector<T> &first, const std::vector<U> &second)
{
    double sum = 0;
    size_t limit = std::min(first.size(), second.size());

    // std::cout << "first:\t" << first.size() << std::endl;
    // std::cout << second.size() << std::endl;
    // exit(EXIT_SUCCESS);

    for (size_t i = 0; i < limit; ++i)
    {
        sum += (double)first[i] * (double)second[i];
    }

    return sum;
}

template <typename T, typename U>
int64_t Modulo(T a, U b)
{
    int64_t m = (int64_t)a % (int64_t)b;
    if (m < 0)
    {
        m = (b < 0) ? m - (int64_t)b : m + (int64_t)b;
    }
    return m;
}

double EuclideanDistance(const std::vector<unsigned char> &first, const std::vector<unsigned char> &second);

double ManhattanDistance(const std::vector<unsigned char> &first, const std::vector<unsigned char> &second);

std::mt19937 &RandGen();

#endif