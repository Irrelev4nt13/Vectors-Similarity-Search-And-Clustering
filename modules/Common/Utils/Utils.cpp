#include <iostream>
#include <vector>
#include <random>
#include <cstdint>
#include <cmath>
#include <tuple>
#include <chrono>

#include "Utils.hpp"

#ifdef DEBUG
#include <unistd.h>
#include <limits.h>
#endif

void readFilenameIfEmpty(std::string &filename, std::string fileType)
{
    if (filename.empty())
    {
        std::cout << "Enter " << fileType << " file: ";
        std::getline(std::cin, filename);
    }
}

#ifdef DEBUG
std::string getFullPath(std::string relativePath)
{
    std::string cwd;
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr)
    {
        cwd = buffer;
    }

    // cwd gets the full path of the file from which the debugger was started
    // run debugger from Makefile for 0 parent folders
    int numParents = 0;
    std::string fullPath = cwd;
    for (int i = 0; i < numParents; i++)
    {
        size_t pos = fullPath.rfind('/');
        if (pos != std::string::npos)
        {
            fullPath = fullPath.substr(0, pos);
        }
    }
    return fullPath + "/" + relativePath;
}
#endif

static std::chrono::high_resolution_clock::time_point startTime;

void startClock() { startTime = std::chrono::high_resolution_clock::now(); }

std::chrono::nanoseconds stopClock()
{
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();

    std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    return duration;
}

double DotProduct(const std::vector<double> &first, const std::vector<double> &second)
{
    double sum = 0.0;
    for (size_t i = 0; i < first.size(); ++i)
        sum += first[i] * second[i];
    return sum;
}

// Binary search in P to find the index corresponding to x
int binarySearch(const std::vector<double> &probs, double x)
{
    int l = 0, r = probs.size() - 1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (probs[mid] < x)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return l;
}

int HammingDistance(const int first, const int second)
{
    int xorResult = first ^ second;
    int distance = 0;

    while (xorResult > 0)
    {
        distance += xorResult & 1;
        xorResult >>= 1;
    }

    return distance;
}

double RealDistribution(int from, int to)
{
    std::uniform_real_distribution<double> rd(from, to);
    return rd(RandGen());
}

int IntDistribution(int from, int to)
{
    std::uniform_int_distribution<int> id(from, to);
    return id(RandGen());
}

double NormalDistribution(double from, double to)
{
    std::normal_distribution<double> nd(from, to);
    return nd(RandGen());
}

std::mt19937 &RandGen()
{
    // static std::random_device rd;
    // static std::mt19937 gen(rd());
    static std::mt19937 gen(0);
    return gen;
}