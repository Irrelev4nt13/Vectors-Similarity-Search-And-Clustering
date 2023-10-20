
#include "PublicTypes.hpp"
#include "Cluster.hpp"
#include "Image.hpp"

Cluster::Cluster(ImagePtr image) : centroid(image) {}

Cluster::~Cluster() {}

ImagePtr Cluster::GetCentroid() { return centroid; }

std::vector<ImagePtr> *Cluster::GetMemberOfCluster() { return &member_of_cluster; }

void Cluster::AddToCluster(ImagePtr image) { member_of_cluster.push_back(image); }
