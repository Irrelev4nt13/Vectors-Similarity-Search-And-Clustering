#ifndef CLUSTERALGORITHMS_HPP_
#define CLUSTERALGORITHMS_HPP_

#include <vector>

#include "PublicTypes.hpp"
#include "Image.hpp"
#include "Cluster.hpp"

std::vector<Cluster> KMeansPlusPlus(std::vector<ImagePtr> input_images, int number_of_clusters);

#endif