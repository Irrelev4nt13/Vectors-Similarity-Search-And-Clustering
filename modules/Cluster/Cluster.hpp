#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_

#include <vector>

#include "PublicTypes.hpp"
#include "Image.hpp"
#include "ImageDistance.hpp"

class Cluster
{
private:
    ImagePtr centroid;
    std::vector<ImagePtr> member_of_cluster;
    int id;
    int prev_len;
    int cur_len;
    ImageDistance *distance;

public:
    Cluster(ImagePtr image, const int id);
    ~Cluster();
    ImagePtr GetCentroid();
    std::vector<ImagePtr> GetMemberOfCluster();
    void AddToCluster(ImagePtr image);
    int GetClusterId();
    void RemoveMember(ImagePtr member);
    void UpdateCentroid(ImagePtr image);
    double AverageDistance(ImagePtr image);
};

#endif