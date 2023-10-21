
#include "PublicTypes.hpp"
#include "Cluster.hpp"
#include "Image.hpp"

Cluster::Cluster(ImagePtr image, const int id) : centroid(image), id(id) {}

Cluster::~Cluster() {}

ImagePtr Cluster::GetCentroid() { return centroid; }

std::vector<ImagePtr> Cluster::GetMemberOfCluster() { return member_of_cluster; }

void Cluster::AddToCluster(ImagePtr image) { member_of_cluster.push_back(image); }

int Cluster::GetClusterId() { return id; }

void Cluster::UpdateCentroid(ImagePtr new_centroid) { centroid = new_centroid; }

void Cluster::UpdateMembers() { member_of_cluster = std::vector<ImagePtr>{}; }