#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <cstdint>
#include <tuple>

#include "PublicTypes.hpp"
#include "Cluster.hpp"

void readFilenameIfEmpty(std::string &filename, std::string fileType);

#ifdef DEBUG
std::string getFullPath(std::string relativePath);
#endif

void startClock();

std::chrono::nanoseconds stopClock();

template <typename T, typename U>
double DotProduct(const std::vector<T> &first, const std::vector<U> &second)
{
    double sum = 0.0;
    for (size_t i = 0; i < first.size(); ++i)
        sum += first[i] * second[i];
    return sum;
}

template <typename T, typename U>
uint8_t Modulo(T a, U b) { return static_cast<uint8_t>(a % b); }

template <typename T, typename U>
double EuclideanDistance(const std::vector<T> &first, const std::vector<U> &second)
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

double ManhattanDistance(const std::vector<double> &first, const std::vector<double> &second);

int binarySearch(const std::vector<double> &probs, double x);

int HammingDistance(const int first, const int second);

double RealDistribution(int from, int to);

int IntDistribution(int from, int to);

double NormalDistribution(double from, double to);

std::mt19937 &RandGen();

#endif