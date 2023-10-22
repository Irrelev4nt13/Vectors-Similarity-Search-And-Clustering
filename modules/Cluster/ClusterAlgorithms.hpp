#ifndef CLUSTERALGORITHMS_HPP_
#define CLUSTERALGORITHMS_HPP_

#include <vector>
#include <unordered_set>

#include "PublicTypes.hpp"
#include "Image.hpp"
#include "Cluster.hpp"
#include "Lsh.hpp"

std::vector<Cluster> KMeansPlusPlus(const std::vector<ImagePtr> &input_images, int number_of_clusters);

std::vector<Cluster> MacQueen(std::vector<Cluster> &clusters, std::unordered_set<int> &ids);

std::vector<Cluster> LloydsAssignment(std::vector<ImagePtr> input_images, int number_of_clusters);

std::vector<Cluster> ReverseRangeSearchLSH(std::vector<ImagePtr> input_images, Lsh lsh, int number_of_clusters);

// std::vector<Cluster> ReverseRangeSearchHyperCube();
std::tuple<double, int, int> MinDistanceToCentroids(const ImagePtr image, std::vector<Cluster> clusters);
double AverageDistance(ImagePtr image, Cluster cluster);
int NextClosestClusterIdx(int cluster_idx, ImagePtr data_point, std::vector<Cluster> clusters);
std::vector<double> Silhouettes(std::vector<Cluster> clusters);
double MinDistanceCentroids(std::vector<Cluster> clusters);
#endif