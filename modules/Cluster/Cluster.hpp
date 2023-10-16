#ifndef CLUSTER_HPP_
#define CLUSTER_HPP_

#include <vector>

#include "Image.hpp"

class Cluster
{
private:
    std::vector<Image *> member_of_cluster;

public:
    Cluster(std::vector<Image *> &members) : member_of_cluster(members) {}
    Cluster(Image *image) { member_of_cluster.push_back(image); }
    Cluster() {}
    ~Cluster() {}
    std::vector<Image *> *GetMemberOfCluster() { return &member_of_cluster; }
    void AddToCluster(Image *image) { member_of_cluster.push_back(image); }
};

#endif