#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_

#include <vector>

#include "PublicTypes.hpp"
#include "Image.hpp"

class Cluster
{
private:
    ImagePtr centroid;
    std::vector<ImagePtr> member_of_cluster;
    int id;

public:
    Cluster(ImagePtr image, const int id);
    ~Cluster();
    ImagePtr GetCentroid();
    std::vector<ImagePtr> GetMemberOfCluster();
    void AddToCluster(ImagePtr image);
    int GetClusterId();
    void UpdateCentroid(ImagePtr new_centroid);
    void UpdateMembers();
};

#endif