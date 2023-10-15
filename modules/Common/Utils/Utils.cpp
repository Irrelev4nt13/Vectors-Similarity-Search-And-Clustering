#include <vector>
#include <random>
#include <cstdint>
#include <cmath>

#include "Utils.hpp"

// void split_cluster_args(const int argc, const char *argv[], ClusterArgs &args)
// {
//     for (int i = 0; i < argc; i++)
//     {
//         if (!strcmp(argv[i], "-i"))
//             args.input_file = std::string(argv[i + 1]);
//         else if (!strcmp(argv[i], "-c"))
//             args.configuration_file = std::string(argv[i + 1]);
//         else if (!strcmp(argv[i], "-o"))
//             args.output_file = std::string(argv[i + 1]);
//         else if (!strcmp(argv[i], "-complete"))
//             args.complete = true;
//         else if (!strcmp(argv[i], "-m"))
//             args.method = std::string(argv[i + 1]);
//     }
// }

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