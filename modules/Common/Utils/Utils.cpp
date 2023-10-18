#include <iostream>
#include <vector>
#include <random>
#include <cstdint>
#include <cmath>

#include "Utils.hpp"

void readFilenameIfEmpty(std::string &filename, std::string fileType)
{
    if (filename.empty())
    {
        std::cout << "Enter " << fileType << " file: ";
        std::getline(std::cin, filename);
    }
}

static std::chrono::_V2::system_clock::time_point startTime;

void startClock()
{
    startTime = std::chrono::high_resolution_clock::now();
}

std::chrono::nanoseconds stopClock()
{
    std::chrono::_V2::system_clock::time_point endTime = std::chrono::high_resolution_clock::now();

    std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(startTime - endTime);

    return duration;
}

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