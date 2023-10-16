#ifndef CLUSTERALGORITHMS_HPP_
#define CLUSTERALGORITHMS_HPP_

#include <vector>

#include "Image.hpp"
#include "Cluster.hpp"

std::vector<Cluster> KMeansPlusPlus(std::vector<Image *> input_images, int number_of_clusters);

#endif