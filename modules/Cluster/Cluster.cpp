#include <vector>
#include <algorithm>

#include "PublicTypes.hpp"
#include "Cluster.hpp"
#include "Image.hpp"
#include "Utils.hpp"

Cluster::Cluster(ImagePtr image, const int id) : centroid(new Image(*image)), id(id), prev_len(0), cur_len(0), distance(ImageDistance::getInstance()) {}

Cluster::~Cluster() {}

ImagePtr Cluster::GetCentroid() { return centroid; }

std::vector<ImagePtr> Cluster::GetMemberOfCluster() { return member_of_cluster; }

void Cluster::AddToCluster(ImagePtr image)
{
    member_of_cluster.push_back(image);
    prev_len = cur_len;
    ++cur_len;
}

int Cluster::GetClusterId() { return id; }

void Cluster::RemoveMember(ImagePtr member)
{
    auto it = std::find(member_of_cluster.begin(), member_of_cluster.end(), member);
    if (it != member_of_cluster.end())
    {
        member_of_cluster.erase(it);
        prev_len = cur_len;
        --cur_len;
    }
}

void Cluster::UpdateCentroid(int from_to, ImagePtr image)
{
    if (from_to == 1) // Point was added
        for (int i = 0; i < centroid->pixels.size(); i++)
            centroid->pixels[i] = centroid->pixels[i] * prev_len / cur_len + image->pixels[i] / cur_len;
    else // Point was removed
    {
        if (cur_len == 0)
            for (auto pixel : centroid->pixels)
                pixel = 0;
        else
            for (int i = 0; i < centroid->pixels.size(); i++)
                centroid->pixels[i] = centroid->pixels[i] * prev_len / cur_len - image->pixels[i] / cur_len;
    }
    /*
    old center = sum of prev points / prev len ==>

    old center * prev len / curr len = sum of prev points / curr len ==>

    old center * prev len / curr len + new point / curr len = (sum of prev points + new point) / curr len = sum of new points / current len

    */
}
