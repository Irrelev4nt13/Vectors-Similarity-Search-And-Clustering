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
#include "Cube.hpp"
#include "ImageDistance.hpp"

ClusterAlgorithms::ClusterAlgorithms()
{
    distanceHelper = ImageDistance::getInstance();
}

ClusterAlgorithms::~ClusterAlgorithms() {}

std::tuple<double, int, int> ClusterAlgorithms::MinDistanceToCentroids(const ImagePtr image, std::vector<Cluster> clusters)
{
    double minDistance = -1;       // Initialize minDistance to a negative value
    double secondMinDistance = -1; // Initialize secondMinDistance to a negative value
    int cluster_id = -1;
    int next_cluster_id = -1;
    bool minDistanceInitialized = false;

    for (std::size_t i = 0; i < clusters.size(); i++)
    {
        double distance = distanceHelper->calculate(clusters[i].GetCentroid(), image);

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

double ClusterAlgorithms::MinDistanceCentroids(std::vector<Cluster> clusters)
{
    double minDistance = -1;
    bool minDistanceInitialized = false;
    for (auto &cluster1 : clusters)
    {
        for (auto &cluster2 : clusters)
        {
            if (&cluster1 != &cluster2)
            { // Avoid comparing a cluster with itself
                double dist = distanceHelper->calculate(cluster1.GetCentroid(), cluster2.GetCentroid());
                if (!minDistanceInitialized)
                {
                    minDistance = dist;
                    minDistanceInitialized = true;
                }
                else if (dist < minDistance)
                    minDistance = dist;
            }
        }
    }

    return minDistance;
}

std::vector<Cluster> ClusterAlgorithms::KMeansPlusPlus(std::vector<ImagePtr> input_images, int number_of_clusters)
{
    std::vector<Cluster> clusters;     // all clusters
    std::unordered_set<int> centroids; // set to remember which centroids have already been chosen

    // choose a random existing data point as an initial centroid in the first cluster
    int first_index = IntDistribution(0, input_images.size() - 1);
    clusters.push_back(Cluster(input_images[first_index], 0));

    // update set
    centroids.insert(input_images[first_index]->id);

    // For each cluster after the first one
    // Calculate the min distance from the images to centroids
    for (int i = 1; i < number_of_clusters; i++)
    {
        std::vector<double> minDistances;
        double normalizer;

        for (std::size_t j = 0; j < input_images.size(); j++)
        {
            // If current image id of dataset matches an id from previously selected centroids, continue
            if (centroids.find(input_images[j]->id) != centroids.end())
            {
                continue;
            }

            // calculate the min distances
            std::tuple<double, int, int> distance_and_id = MinDistanceToCentroids(input_images[j], clusters);

            double distance = std::get<0>(distance_and_id);
            if (distance > normalizer)
                normalizer = distance;

            minDistances.push_back(distance);
        }

        // size: n - t where t increases by 1 after each cluster has been initialized
        int probs_size = input_images.size() - centroids.size();

        // probabilities
        std::vector<double> probs(probs_size);

        // Get the max from the min distances in order to later normalize the distances
        double maxD = *max_element(minDistances.begin(), minDistances.end());

        // calculate partial sums
        double sum = 0;
        for (int r = 0; r < probs_size; r++)
        {
            minDistances[r] /= maxD; // normalize
            sum += pow(minDistances[r], 2);
            probs[r] = sum;
        }

        // random x with uniform real distriubution in the range of the probabilities values
        double x = RealDistribution(0, probs[probs_size - 1]);

        // apply binary search for x in probs vector and find the corresponding index
        int idx = binarySearch(probs, x);

        // update set and clusters
        centroids.insert(idx);
        clusters.push_back(Cluster(input_images[idx], i));
    }
    return clusters;
}

void ClusterAlgorithms::MacQueen(std::vector<Cluster> &clusters, int prev_clust, int new_clust, ImagePtr image)
{
    if (prev_clust != -1)
    {
        clusters[prev_clust].RemoveMember(image);
        clusters[prev_clust].UpdateCentroid(image);
    }
    clusters[new_clust].UpdateCentroid(image);
}

std::vector<Cluster> ClusterAlgorithms::LloydsAssignment(std::vector<ImagePtr> input_images, int number_of_clusters)
{
    std::vector<Cluster> clusters = KMeansPlusPlus(input_images, number_of_clusters);

    std::unordered_map<int, int> assigned_images;

    while (true)
    {
        int assignment_occurred = 0;
        for (auto image : input_images)
        {
            std::tuple<double, int, int> distance_and_id = MinDistanceToCentroids(image, clusters);

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

void ClusterAlgorithms::ReverseAssignment(std::vector<Cluster> &clusters,
                                          std::vector<ImagePtr> RangeSearch,
                                          std::unordered_map<int, int> &assigned_images,
                                          int &assignment_occurred,
                                          int &assignment_occurred_inner, int candidate_cluster)
{
    for (auto image : RangeSearch)
    {
        if (assigned_images.find(image->id) == assigned_images.end())
        {
            assignment_occurred++;
            assignment_occurred_inner++;
            assigned_images[image->id] = candidate_cluster;
            clusters[candidate_cluster].AddToCluster(image);
            MacQueen(clusters, -1, candidate_cluster, image);
        }
        else
        {
            double candidate_cluster_distance = distanceHelper->calculate(clusters[candidate_cluster].GetCentroid(), image);
            double cur_cluster_distance = distanceHelper->calculate(clusters[assigned_images[image->id]].GetCentroid(), image);
            if (candidate_cluster_distance < cur_cluster_distance)
            {
                assignment_occurred++;
                assignment_occurred_inner++;
                int prev_clust = assigned_images[image->id];
                assigned_images[image->id] = candidate_cluster;
                clusters[candidate_cluster].AddToCluster(image);
                MacQueen(clusters, prev_clust, candidate_cluster, image);
            }
        }
    }
}

void ClusterAlgorithms::LloydsForRest(std::vector<ImagePtr> input_images,
                                      std::vector<Cluster> &clusters,
                                      std::unordered_map<int, int> &assigned_images,
                                      int &assignment_occurred)
{
    for (auto image : input_images)
    {
        auto entry = assigned_images.find(image->id);
        if (entry == assigned_images.end())
        {
            assignment_occurred++;
            std::tuple<double, int, int> distance_id_nextid = MinDistanceToCentroids(image, clusters);
            clusters[std::get<1>(distance_id_nextid)].AddToCluster(image);
            assigned_images[image->id] = std::get<1>(distance_id_nextid);
            MacQueen(clusters, -1, std::get<1>(distance_id_nextid), image);
        }
    }
}

std::vector<Cluster> ClusterAlgorithms::ReverseRangeSearchLSH(std::vector<ImagePtr> input_images, Lsh lsh, int number_of_clusters)
{
    std::vector<Cluster> clusters = KMeansPlusPlus(input_images, number_of_clusters);
    std::unordered_map<int, int> assigned_images;
    while (true)
    {
        int assignment_occurred = 0;
        double radius = MinDistanceCentroids(clusters) / 2.0;
        while (true)
        {
            int assignment_occurred_inner = 0;
            for (int i = 0; i < number_of_clusters; i++)
            {
                std::vector<ImagePtr> RangeSearch = lsh.Approximate_Range_Search(clusters[i].GetCentroid(), radius);
                ReverseAssignment(clusters, RangeSearch, assigned_images, assignment_occurred, assignment_occurred_inner, i);
            }
            if (assignment_occurred_inner == 0)
                break;
            radius *= 2;
        }
        LloydsForRest(input_images, clusters, assigned_images, assignment_occurred);
        if (assignment_occurred == 0)
            break;
    }
    return clusters;
}

std::vector<Cluster> ClusterAlgorithms::ReverseRangeSearchHyperCube(std::vector<ImagePtr> input_images, Cube &cube, int number_of_clusters)
{
    std::vector<Cluster> clusters = KMeansPlusPlus(input_images, number_of_clusters);
    std::unordered_map<int, int> assigned_images;
    while (true)
    {
        int assignment_occurred = 0;
        double radius = MinDistanceCentroids(clusters) / 2.0;
        while (true)
        {
            int assignment_occurred_inner = 0;
            for (int i = 0; i < number_of_clusters; i++)
            {
                std::vector<ImagePtr> RangeSearch = cube.Approximate_Range_Search(clusters[i].GetCentroid(), radius);
                ReverseAssignment(clusters, RangeSearch, assigned_images, assignment_occurred, assignment_occurred_inner, i);
            }
            if (assignment_occurred_inner == 0)
                break;
            radius *= 2;
        }
        LloydsForRest(input_images, clusters, assigned_images, assignment_occurred);
        if (assignment_occurred == 0)
            break;
    }
    return clusters;
}

std::tuple<std::vector<double>, double> ClusterAlgorithms::Silhouettes(std::vector<Cluster> clusters)
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
