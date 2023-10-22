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

std::vector<Cluster> KMeansPlusPlus(std::vector<ImagePtr> input_images, int number_of_clusters)
{
    std::vector<Cluster> clusters;
    std::unordered_set<int> centroids;

    int first_index = IntDistribution(0, input_images.size() - 1);
    clusters.push_back(Cluster(input_images[first_index], 0));
    centroids.insert(input_images[first_index]->id);

    for (int i = 1; i < number_of_clusters; i++)
    {
        int vec_size = input_images.size() - number_of_clusters;
        std::vector<double> minDistances;
        double normalizer;

        for (const auto &image : input_images)
        {
            if (centroids.find(image->id) == centroids.end())
            {
                std::tuple<double, int, int> distance_and_id = MinDistanceToCentroids(image, clusters);

                double distance = std::get<0>(distance_and_id);
                if (distance > normalizer)
                    normalizer = distance;

                minDistances.push_back(distance);
            }
        }

        int probs_size = minDistances.size();
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
            new_centroid->pixels[i] = new_centroid->pixels[i] / T;
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
            // std::cout << "Pass: " << std::get<0>(distance_and_id) << " " << std::get<1>(distance_and_id) << " " << std::get<2>(distance_and_id) << std::endl;
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

std::vector<Cluster> ReverseRangeSearchLSH(std::vector<ImagePtr> input_images, Lsh lsh, int number_of_clusters)
{
    std::vector<Cluster> clusters = KMeansPlusPlus(input_images, number_of_clusters);
    std::unordered_map<int, int> assigned_images;
    std::unordered_set<int> ids;
    int epochs = 0;

    while (true)
    {
        int assignment_occurred = 0;
        bool found_at_least_one_assignment;
        double max_radius = MinDistanceCentroids(clusters) / 2.0;

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
        epochs++;
        if (assignment_occurred == 0)
            break;
        else
        {
            clusters = MacQueen(clusters, ids);
            // exit(1);
        }
    }
    return clusters;
}

// std::vector<Cluster> ReverseRangeSearchHyperCube();

std::tuple<double, int, int> MinDistanceToCentroids(const ImagePtr image, std::vector<Cluster> clusters)
{
    double minDistance;
    int cluster_id;
    int next_cluster_id;
    for (std::size_t i = 0; i < clusters.size(); i++)
    {
        double distance = EuclideanDistance(clusters[i].GetCentroid()->pixels, image->pixels);
        if (i == 0)
        {
            minDistance = distance;
            next_cluster_id = i;
            cluster_id = i;
        }
        else if (distance < minDistance)
        {
            minDistance = distance;
            next_cluster_id = cluster_id;
            cluster_id = i;
        }
    }
    return std::tuple<double, int, int>{minDistance, cluster_id, next_cluster_id};
}

double AverageDistance(ImagePtr image, Cluster cluster)
{
    int n_members = cluster.GetMemberOfCluster().size();
    std::vector<ImagePtr> members = cluster.GetMemberOfCluster();

    int contains_it = 0; // Is set to 1 if 'cluster' contains 'data_point'
    double avg_dist = 0.0;
    for (int i = 0; i < n_members; i++)
        if (image->id != members[i]->id)
            avg_dist += EuclideanDistance(members[i]->pixels, image->pixels);
        else
            contains_it = 1;

    // Careful: don't count dist from 'data_point' to itself, if 'cluster' contains it
    return n_members - contains_it != 0 ? avg_dist / (n_members - contains_it) : -1;
}

int NextClosestClusterIdx(int cluster_idx, ImagePtr data_point, std::vector<Cluster> clusters)
{
    double min_distance = -1;
    int next_best_cluster_idx = 0;

    for (int i = 0, k_clusters = clusters.size(); i < k_clusters; i++)
    {
        if (i != cluster_idx)
        {
            double curr_dist = EuclideanDistance(clusters[i].GetCentroid()->pixels, data_point->pixels);

            if (curr_dist < min_distance || min_distance == -1)
            {
                min_distance = curr_dist;
                next_best_cluster_idx = i;
            }
        }
    }

    return next_best_cluster_idx;
}

std::vector<double> Silhouettes(std::vector<Cluster> clusters)
{
    std::vector<double> silhouettes;
    int num_of_clusters = clusters.size();
    for (int i = 0; i < num_of_clusters; i++)
    {
        double curSilhouette = 0.0;
        // Needs to change and be done into another function
        std::vector<ImagePtr> members = clusters[i].GetMemberOfCluster();
        for (std::size_t j = 0; j < members.size(); j++)
        {
            // std::tuple<double, int, int> temp = MinDistanceToCentroids(members[j], clusters);
            double avg_dist = AverageDistance(members[j], clusters[i]);
            double avg_dist_next_closest = AverageDistance(members[j], clusters[NextClosestClusterIdx(i, members[j], clusters)]);
            curSilhouette += (avg_dist_next_closest - avg_dist) / std::max(avg_dist, avg_dist_next_closest);
        }
        silhouettes.push_back(curSilhouette / clusters[i].GetMemberOfCluster().size());
    }
    // double curClusterShilhouette = ClusterShilhouette(clusters[i]);
    // silhouettes.push_back(curClusterShilhouette);
    return silhouettes;
}

double MinDistanceCentroids(std::vector<Cluster> clusters)
{
    double min_dist = -1;

    for (int i = 0, n_centroids = clusters.size(); i < n_centroids - 1; i++)
    {
        for (int j = i + 1; j < n_centroids; j++)
        {
            double dist = EuclideanDistance(clusters[i].GetCentroid()->pixels, clusters[j].GetCentroid()->pixels);
            if (dist < min_dist || min_dist == -1)
            {
                min_dist = dist;
            }
        }
    }

    return min_dist;
}