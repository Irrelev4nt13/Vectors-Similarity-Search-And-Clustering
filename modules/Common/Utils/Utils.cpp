#include <vector>
#include <random>
#include <cstdint>
#include <cmath>

#include "Utils.hpp"

double EuclideanDistance(const std::vector<uint8_t> &first, const std::vector<uint8_t> &second)
{
    double difference, result = 0.0;
    size_t limit = first.size();
    for (size_t i = 0; i < limit; i++)
    {
        difference = first[i] - second[i];
        result += difference * difference;
    }
    return sqrt(result);
}

double ManhattanDistance(const std::vector<uint8_t> &first, const std::vector<uint8_t> &second)
{
    double result = 0;
    size_t limit = first.size();
    for (size_t i = 0; i < limit; i++)
        result += std::abs(first[i] - second[i]);
    return result;
}

std::mt19937 &RandGen()
{
    // static std::random_device rd;
    // static std::mt19937 gen(rd());
    static std::mt19937 gen(0);
    return gen;
}