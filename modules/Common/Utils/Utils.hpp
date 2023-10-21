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

double EuclideanDistance(const std::vector<uint8_t> &first, const std::vector<uint8_t> &second);

double ManhattanDistance(const std::vector<uint8_t> &first, const std::vector<uint8_t> &second);

int HammingDistance(const int first, const int second);

std::mt19937 &RandGen();

#endif