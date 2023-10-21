
#include "PublicTypes.hpp"
#include "Cluster.hpp"
#include "Image.hpp"
#include "Utils.hpp"

Cluster::Cluster(Image image, const int id) : centroid(image), id(id)
{
    // std::vector<double> double_vector;
    // for (uint8_t element : image->pixels)
    // {
    //     double converted_element = static_cast<double>(element);
    //     double_vector.push_back(converted_element);
    // }
    // centroid = Centroid(image->id, double_vector);
}
Cluster::Cluster(ImagePtr image, const int id) : centroid(*image), id(id) {}
// Cluster::Cluster(Centroid image, const int id) : centroid(image), id(id) {}

Cluster::~Cluster()
{
}

// Centroid Cluster::GetCentroid() { return centroid; }
Image Cluster::GetCentroid() { return centroid; }

std::vector<ImagePtr> Cluster::GetMemberOfCluster() { return member_of_cluster; }

void Cluster::AddToCluster(ImagePtr image) { member_of_cluster.push_back(image); }

int Cluster::GetClusterId() { return id; }

// void Cluster::UpdateCentroid(ImagePtr new_centroid) { centroid = new_centroid; }

// void Cluster::UpdateMembers() { member_of_cluster = std::vector<ImagePtr>{}; }

std::tuple<double, int, int> MinDistanceToCentroids(const ImagePtr image, std::vector<Cluster> clusters)
{
    double minDistance;
    int cluster_id;
    int next_cluster_id;
    for (std::size_t i = 0; i < clusters.size(); i++)
    {
        double distance = EuclideanDistance(clusters[i].GetCentroid().pixels, image->pixels);
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
            double curr_dist = EuclideanDistance(clusters[i].GetCentroid().pixels, data_point->pixels);

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
