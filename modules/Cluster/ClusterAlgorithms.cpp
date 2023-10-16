#include <vector>
#include <random>

#include "Utils.hpp"
#include "Image.hpp"
#include "Cluster.hpp"
#include "ClusterAlgorithms.hpp"

std::vector<Cluster> KMeansPlusPlus(std::vector<Image *> input_images, int number_of_clusters)
{
    std::uniform_int_distribution<> uniform_int(0, input_images.size());

    int index = uniform_int(RandGen());

    std::vector<Cluster> clusters;
    clusters.push_back(Cluster(input_images[index]));
    for (int t = 1; t < number_of_clusters; t++)
    {
        std::vector<double> distance;

        std::vector<double> prob;
    }
    return clusters;
}
