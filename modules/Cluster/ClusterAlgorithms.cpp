#include <vector>
#include <random>
#include <unordered_set>
#include <cstdint>

#include "PublicTypes.hpp"
#include "Utils.hpp"
#include "Image.hpp"
#include "Cluster.hpp"
#include "ClusterAlgorithms.hpp"

std::vector<Cluster> KMeansPlusPlus(std::vector<ImagePtr> input_images, int number_of_clusters)
{
    std::vector<Cluster> clusters;
    std::unordered_set<int> centroids;
    std::uniform_int_distribution<> uniform_int(0, input_images.size() - 1);

    int first_index = uniform_int(RandGen());
    clusters.push_back(Cluster(input_images[first_index]));
    centroids.insert(input_images[first_index]->id);
    for (int i = 1; i < number_of_clusters; i++)
    {
        std::vector<double> minDistances;
        std::vector<double> propabilities;
        // propabilities.push_back(0);
        std::vector<ImagePtr> centroid_candidates;
        double normalizer;
        // for (auto image : input_images)
        for (int j = 0; j < input_images.size(); j++)
        {
            if (centroids.find(input_images[j]->id) == centroids.end())
            {
                double distance = MinDistanceToCentroids(input_images[j], clusters);
                if (j == 0)
                    normalizer = distance;
                else if (distance > normalizer)
                    normalizer = distance;
                minDistances.push_back(distance);
            }
            else
                minDistances.push_back(0);
        }

        double dist_squared_sum = 0;
        for (double &min_dist : minDistances)
        {
            min_dist /= normalizer;
            dist_squared_sum += min_dist * min_dist;
        }

        // Compute the probability for choosing a data point as the next cluster
        int idx = 0;
        for (const ImagePtr data_point : input_images)
        {
            if (centroids.find(data_point->id) == centroids.end())
            {
                propabilities.push_back((minDistances[idx] * minDistances[idx]) / dist_squared_sum);
                idx++;
            }
        }

        // Choose a random data point as next cluster, based on its probability
        idx = 0;
        std::uniform_real_distribution<float> uniform_real(0, 1);
        double cumulative_prob = 0.0, random_prob = uniform_real(RandGen());
        for (const ImagePtr data_point : input_images)
        {
            if (centroids.find(data_point->id) == centroids.end())
            {
                cumulative_prob += propabilities[idx++];
                if (random_prob <= cumulative_prob)
                {
                    clusters.push_back(Cluster(data_point));
                    centroids.insert(data_point->id);
                    break;
                }
            }
        }
    }
    return clusters;
}
