#include <vector>
#include <random>
#include <unordered_set>
#include <cstdint>
#include <tuple>
#include <unordered_map>

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
    clusters.push_back(Cluster(input_images[first_index], 0));
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
                std::tuple<double, int, int> distance_and_id = MinDistanceToCentroids(input_images[j], clusters);
                if (j == 0)
                    normalizer = std::get<0>(distance_and_id);
                else if (std::get<0>(distance_and_id) > normalizer)
                    normalizer = std::get<0>(distance_and_id);
                minDistances.push_back(std::get<0>(distance_and_id));
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
                    clusters.push_back(Cluster(data_point, i));
                    centroids.insert(data_point->id);
                    break;
                }
            }
        }
    }
    return clusters;
}

std::vector<Cluster> MacQueen(std::vector<Cluster> &clusters, std::unordered_set<int> &ids)
{
    // for (auto id : ids)
    std::vector<Cluster> new_clust;
    for (auto cluster : clusters)
    {
        /*
            old center = sum of prev points / prev len ==>

            old center * prev len / curr len = sum of prev points / curr len ==>

            old center * prev len / curr len + new point / curr len = (sum of prev points + new point) / curr len = sum of new points / current len

         */

        int T = cluster.GetMemberOfCluster().size();
        // int T = clusters[id].GetMemberOfCluster().size();
        std::vector<ImagePtr> members = cluster.GetMemberOfCluster();
        int limit = (int)cluster.GetCentroid()->pixels.size();
        ImagePtr new_centroid = cluster.GetCentroid();
        for (int i = 0; i < limit; i++)
        {
            for (int j = 0; j < T; j++)
                new_centroid->pixels[i] += members[j]->pixels[i];
            new_centroid->pixels[i] = floor(new_centroid->pixels[i] / T);
            // new
        }
        new_clust.push_back(Cluster(new_centroid, cluster.GetClusterId()));
        // cluster.UpdateMembers();
    }
    // ids.clear();
    return new_clust;
}

std::vector<Cluster> LloydsAssignment(std::vector<ImagePtr> input_images, int number_of_clusters)
{
    std::vector<Cluster> clusters = KMeansPlusPlus(input_images, number_of_clusters);
    std::unordered_set<int> ids;
    // First the image id, second the cluster id
    std::unordered_map<int, int> assigned_images;
    int epochs = 0;
    while (true)
    {
        int assignment_occurred = 0;
        for (auto image : input_images)
        {
            std::tuple<double, int, int> distance_and_id = MinDistanceToCentroids(image, clusters);
            std::cout << "Pass: " << std::get<0>(distance_and_id) << " " << std::get<1>(distance_and_id) << " " << std::get<2>(distance_and_id) << std::endl;
            // if (std::get<0>(distance_and_id) != 0)
            // {
            clusters[std::get<1>(distance_and_id)].AddToCluster(image);

            if (assigned_images.find(image->id) == assigned_images.end() || assigned_images[image->id] != std::get<1>(distance_and_id))
            {
                // if (ids.find(std::get<1>(distance_and_id)) == ids.end())
                //     ids.insert(std::get<1>(distance_and_id));
                assigned_images[image->id] = std::get<1>(distance_and_id);
                assignment_occurred++;
            }

            // break;
            // }
        }
        epochs++;
        if (assignment_occurred == 0)
            break;
        else
        {
            clusters = MacQueen(clusters, ids);
            // exit(1);
        }

        // int res = 0;
        // for (auto cluster : clusters)
        // {
        //     std::cout << "Size: " << cluster.GetMemberOfCluster().size() << std::endl;
        //     // std::cout << "Size: " << cluster.GetMemberOfCluster()[0] << std::endl;
        //     res += cluster.GetMemberOfCluster().size();
        // }
        // std::cout << res << std::endl;
    }
    std::cout << "Data was clustered after: " << epochs << " epochs" << std::endl;
    return clusters;
}

// std::vector<Cluster> ReverseRangeSearchLSH();

// std::vector<Cluster> ReverseRangeSearchHyperCube();