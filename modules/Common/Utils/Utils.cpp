#include <iostream>
#include <vector>
#include <random>
#include <cstdint>
#include <cmath>

#include "Utils.hpp"

void readFilenameIfEmpty(std::string &filename)
{
    if (filename.empty())
    {
        std::cout << "Enter " << filename << " file: ";
        std::getline(std::cin, filename);
    }
}

std::chrono::nanoseconds clockUtil(ClockEnum action)
{
    static std::chrono::_V2::system_clock::time_point startTime;

    if (action == ClockEnum::BEGIN)
    {
        startTime = std::chrono::high_resolution_clock::now();
    }
    else if (action == ClockEnum::END)
    {
        std::chrono::_V2::system_clock::time_point endTime = std::chrono::high_resolution_clock::now();

        std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(startTime - endTime);

        return duration;
    }
    else
    {
        return std::chrono::nanoseconds(0);
    }
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