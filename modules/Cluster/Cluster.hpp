#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_

#include <vector>

#include "PublicTypes.hpp"
#include "Image.hpp"

class Centroid
{
public:
    int id;
    std::vector<double> pixels;

    Centroid(int id, const std::vector<double> &pixels) : id(id), pixels(pixels) {}

    Centroid() {}

    ~Centroid() {}
};

class Cluster
{
private:
    Centroid centroid;
    std::vector<ImagePtr> member_of_cluster;
    int id;

public:
    Cluster(ImagePtr image, const int id);
    Cluster(Centroid image, const int id);
    ~Cluster();
    Centroid GetCentroid();
    std::vector<ImagePtr> GetMemberOfCluster();
    void AddToCluster(ImagePtr image);
    int GetClusterId();
    // void UpdateCentroid(ImagePtr new_centroid);
    // void UpdateMembers();
};
std::tuple<double, int, int> MinDistanceToCentroids(const ImagePtr image, std::vector<Cluster> clusters);
double AverageDistance(ImagePtr image, Cluster cluster);
int NextClosestClusterIdx(int cluster_idx, ImagePtr data_point, std::vector<Cluster> clusters);
std::vector<double> Silhouettes(std::vector<Cluster> clusters);

#endif