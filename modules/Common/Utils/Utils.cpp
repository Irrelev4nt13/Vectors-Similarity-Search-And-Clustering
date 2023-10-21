#include <iostream>
#include <vector>
#include <random>
#include <cstdint>
#include <cmath>
#include <tuple>

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

void startClock() { startTime = std::chrono::high_resolution_clock::now(); }

std::chrono::nanoseconds stopClock()
{
    std::chrono::_V2::system_clock::time_point endTime = std::chrono::high_resolution_clock::now();

    std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

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

int HammingDistance(const int first, const int second) { return __builtin_popcount(first ^ second); }

std::tuple<double, int, int> MinDistanceToCentroids(const ImagePtr image, std::vector<Cluster> clusters)
{
    double minDistance;
    int cluster_id;
    int next_cluster_id;
    for (int i = 0; i < clusters.size(); i++)
    {
        double distance = EuclideanDistance(clusters[i].GetCentroid()->pixels, image->pixels);
        if (i == 0)
        {
            minDistance = distance;
            next_cluster_id = i;
            cluster_id = i;
        }
        else if (distance < minDistance)
        {
            minDistance = distance;
            next_cluster_id = cluster_id;
            cluster_id = i;
        }
    }
    return std::tuple<double, int, int>{minDistance, cluster_id, next_cluster_id};
}

// int BinarySearch();

static double AverageDistance(ImagePtr image, Cluster cluster)
{
    int n_members = cluster.GetMemberOfCluster().size();
    std::vector<ImagePtr> members = cluster.GetMemberOfCluster();

    int contains_it = 0; // Is set to 1 if 'cluster' contains 'data_point'
    double avg_dist = 0.0;
    for (int i = 0; i < n_members; i++)
        if (image->id != members[i]->id)
            avg_dist += EuclideanDistance(members[i]->pixels, image->pixels);
        else
            contains_it = 1;

    // Careful: don't count dist from 'data_point' to itself, if 'cluster' contains it
    return n_members - contains_it != 0 ? avg_dist / (n_members - contains_it) : -1;
}

// static double ClusterShilhouette(Cluster cluster)
// {
//     int size = cluster.GetMemberOfCluster().size();
//     std::vector<ImagePtr> members = cluster.GetMemberOfCluster();
//     for (int i = 0; i < size; i++)
//     {
//     }
// }
static int NextClosestClusterIdx(int cluster_idx, ImagePtr data_point, std::vector<Cluster> clusters)
{
    double min_distance = -1;
    int next_best_cluster_idx = 0;

    for (int i = 0, k_clusters = clusters.size(); i < k_clusters; i++)
    {
        if (i != cluster_idx)
        {
            double curr_dist = EuclideanDistance(clusters[i].GetCentroid()->pixels, data_point->pixels);

            if (curr_dist < min_distance || min_distance == -1)
            {
                min_distance = curr_dist;
                next_best_cluster_idx = i;
            }
        }
    }

    return next_best_cluster_idx;
}
std::vector<double> Silhouettes(std::vector<Cluster> clusters)
{
    std::vector<double> silhouettes;
    int num_of_clusters = clusters.size();
    for (int i = 0; i < 1; i++)
    {
        double curSilhouette = 0.0;
        // Needs to change and be done into another function
        std::vector<ImagePtr> members = clusters[i].GetMemberOfCluster();
        for (int j = 0; j < members.size(); j++)
        {
            // std::tuple<double, int, int> temp = MinDistanceToCentroids(members[j], clusters);
            double avg_dist = AverageDistance(members[j], clusters[i]);
            double avg_dist_next_closest = AverageDistance(members[j], clusters[NextClosestClusterIdx(i, members[j], clusters)]);
            curSilhouette += (avg_dist_next_closest - avg_dist) / std::max(avg_dist, avg_dist_next_closest);
        }
        silhouettes.push_back(curSilhouette / clusters[i].GetMemberOfCluster().size());
    }
    // double curClusterShilhouette = ClusterShilhouette(clusters[i]);
    // silhouettes.push_back(curClusterShilhouette);
    return silhouettes;
}

std::mt19937 &RandGen()
{
    // static std::random_device rd;
    // static std::mt19937 gen(rd());
    static std::mt19937 gen(0);
    return gen;
}