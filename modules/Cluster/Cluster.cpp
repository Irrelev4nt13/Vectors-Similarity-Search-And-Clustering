
#include "PublicTypes.hpp"
#include "Cluster.hpp"
#include "Image.hpp"
#include "Utils.hpp"

// Cluster::Cluster(Image image, const int id) : centroid(image), id(id) { distance = ImageDistance::getInstance(); }
Cluster::Cluster(ImagePtr image, const int id) : centroid(new Image(*image)), id(id), distance(ImageDistance::getInstance()) {}

Cluster::~Cluster() {}

ImagePtr Cluster::GetCentroid() { return centroid; }

std::vector<ImagePtr> Cluster::GetMemberOfCluster() { return member_of_cluster; }

void Cluster::AddToCluster(ImagePtr image) { member_of_cluster.push_back(image); }

int Cluster::GetClusterId() { return id; }

void UpdateMembers() {}
void UpdateCentroid() {}
