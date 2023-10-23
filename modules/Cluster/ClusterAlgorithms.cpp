#include <vector>
#include <unordered_set>
#include <cstdint>
#include <tuple>
#include <unordered_map>
#include <algorithm>

#include "PublicTypes.hpp"
#include "Utils.hpp"
#include "Image.hpp"
#include "Cluster.hpp"
#include "ClusterAlgorithms.hpp"
#include "Lsh.hpp"

static std::tuple<double, int, int> MinDistanceToCentroids(const ImagePtr image, std::vector<Cluster> clusters)
{
    double minDistance = -1;       // Initialize minDistance to a negative value
    double secondMinDistance = -1; // Initialize secondMinDistance to a negative value
    int cluster_id = -1;
    int next_cluster_id = -1;
    bool minDistanceInitialized = false;

    for (std::size_t i = 0; i < clusters.size(); i++)
    {
        double distance = EuclideanDistance(clusters[i].GetCentroid()->pixels, image->pixels);

        if (!minDistanceInitialized)
        {
            minDistance = distance;
            cluster_id = i;
            minDistanceInitialized = true;
        }
        else if (distance < minDistance)
        {
            secondMinDistance = minDistance;
            next_cluster_id = cluster_id;
            minDistance = distance;
            cluster_id = i;
        }
        else if (distance < secondMinDistance || secondMinDistance == -1)
        {
            secondMinDistance = distance;
            next_cluster_id = i;
        }
    }
    return std::tuple<double, int, int>{minDistance, cluster_id, next_cluster_id};
}

std::vector<Cluster> KMeansPlusPlus(std::vector<ImagePtr> input_images, int number_of_clusters)
{
    std::vector<Cluster> clusters;
    std::unordered_set<int> centroids;

    int first_index = IntDistribution(0, input_images.size() - 1);
    clusters.push_back(Cluster(input_images[first_index], 0));
    centroids.insert(input_images[first_index]->id);

    for (int i = 1; i < number_of_clusters; i++)
    {
        std::vector<double> minDistances;
        double normalizer;

        for (std::size_t j = 0; j < input_images.size(); j++)
        {
            if (centroids.find(input_images[j]->id) == centroids.end())
            {
                std::tuple<double, int, int> distance_and_id = MinDistanceToCentroids(input_images[j], clusters);

                double distance = std::get<0>(distance_and_id);
                if (distance > normalizer)
                    normalizer = distance;

                minDistances.push_back(distance);
            }
        }

        int probs_size = input_images.size() - centroids.size();
        std::vector<double> probs(probs_size);

        double maxD = *max_element(minDistances.begin(), minDistances.end());

        // calculate partial sums
        double sum = 0;
        for (int r = 0; r < probs_size; r++)
        {
            minDistances[r] /= maxD; // normalize
            sum += pow(minDistances[r], 2);
            probs[r] = sum;
        }

        double x = RealDistribution(0, probs[probs_size - 1]);

        int idx = binarySearch(probs, x);

        centroids.insert(idx);

        clusters.push_back(Cluster(input_images[idx], i));
    }
    return clusters;
}

void MacQueen(std::vector<Cluster> &clusters, int prev_clust, int new_clust, ImagePtr image)
{
    if (prev_clust != -1)
    {
        clusters[prev_clust].RemoveMember(image);
        clusters[prev_clust].UpdateCentroid(image);
    }
    clusters[new_clust].UpdateCentroid(image);
}

std::vector<Cluster> LloydsAssignment(std::vector<ImagePtr> input_images, int number_of_clusters)
{
    std::vector<Cluster> clusters = KMeansPlusPlus(input_images, number_of_clusters);

    std::unordered_map<int, int> assigned_images;

    while (true)
    {
        int assignment_occurred = 0;
        for (auto image : input_images)
        {
            std::tuple<double, int, int> distance_and_id = MinDistanceToCentroids(image, clusters);

            auto is_assigned = assigned_images.find(image->id);
            if (assigned_images.find(image->id) == assigned_images.end())
            {
                // No assignments before
                assignment_occurred++;
                assigned_images[image->id] = std::get<1>(distance_and_id);
                clusters[std::get<1>(distance_and_id)].AddToCluster(image);
                MacQueen(clusters, -1, std::get<1>(distance_and_id), image);
            }
            else // Have been assigned at least once
            {
                if (assigned_images[image->id] != std::get<1>(distance_and_id))
                { // Re-assign only if the new cluster is different
                    assignment_occurred++;
                    int prev_clust = assigned_images[image->id];
                    assigned_images[image->id] = std::get<1>(distance_and_id);
                    clusters[std::get<1>(distance_and_id)].AddToCluster(image);
                    MacQueen(clusters, prev_clust, std::get<1>(distance_and_id), image);
                }
            }
        }
        if (assignment_occurred == 0)
            break;
    }
    return clusters;
}

std::vector<Cluster> ReverseRangeSearchLSH(std::vector<ImagePtr> input_images, Lsh lsh, int number_of_clusters)
{
    std::vector<Cluster> clusters = KMeansPlusPlus(input_images, number_of_clusters);
    std::unordered_map<int, int> assigned_images;
    while (true)
    {
        int assignment_occurred = 0;
        bool found_at_least_one_assignment;
        double max_radius; // = MinDistanceCentroids(clusters) / 2.0;
        do
        {
            // Assign data points using progressively expanding range searches around centroids
            // until we reach a point where there are no new assignments => continue with Lloyd's
            found_at_least_one_assignment = false;
            for (int i = 0; i < number_of_clusters; i++)
            {
                ImagePtr centroid = clusters[i].GetCentroid();
                std::vector<ImagePtr> points_inside_range = lsh.Approximate_Range_Search(centroid, max_radius);
                for (auto data_point : points_inside_range)
                {
                    auto entry = assigned_images.find(data_point->id);
                    if (entry == assigned_images.end())
                    {
                        assignment_occurred++;
                        found_at_least_one_assignment = true;
                        assigned_images[data_point->id] = i;
                    }
                    else
                    {
                        double dist1 = EuclideanDistance(clusters[i].GetCentroid()->pixels, data_point->pixels);
                        double dist2 = EuclideanDistance(clusters[entry->second].GetCentroid()->pixels, data_point->pixels);
                        // Only assign current data point to current cluster if it's closer to it
                        if (dist1 < dist2)
                        {
                            assignment_occurred++;
                            found_at_least_one_assignment = true;
                            assigned_images[data_point->id] = i;
                        }
                    }
                }
            }
            max_radius *= 2;
        } while (found_at_least_one_assignment);
        for (auto data_point : input_images)
        {
            auto entry = assigned_images.find(data_point->id);
            if (entry == assigned_images.end())
            {
                assignment_occurred++;
                std::tuple<double, int, int> temp = MinDistanceToCentroids(data_point, clusters);
                clusters[std::get<1>(temp)].AddToCluster(data_point);
                assigned_images[data_point->id] = std::get<1>(temp);
            }
            else
            {
                clusters[entry->second].AddToCluster(data_point);
            }
        }
        if (assignment_occurred == 0)
            break;
    }
    return clusters;
}

// std::vector<Cluster> ReverseRangeSearchHyperCube();

std::tuple<std::vector<double>, double> Silhouettes(std::vector<Cluster> clusters)
{
    std::vector<double> silhouettes;
    int num_of_clusters = clusters.size();
    double stotal = 0.0;
    int total_members = 0;
    for (int i = 0; i < num_of_clusters; i++)
    {
        double si = 0.0;
        std::vector<ImagePtr> members = clusters[i].GetMemberOfCluster();
        for (auto member : clusters[i].GetMemberOfCluster())
        {
            double ai = clusters[i].AverageDistance(member);
            double bi = clusters[std::get<2>(MinDistanceToCentroids(member, clusters))].AverageDistance(member);
            si += (bi - ai) / std::max(ai, bi);
        }
        stotal += si;
        total_members += clusters[i].GetMemberOfCluster().size();
        silhouettes.push_back(si / clusters[i].GetMemberOfCluster().size());
    }
    return std::tuple<std::vector<double>, double>{silhouettes, stotal / total_members};
}
