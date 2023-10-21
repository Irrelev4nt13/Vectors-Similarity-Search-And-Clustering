#include <iostream>
#include <fstream>
#include <iomanip>

#include "PublicTypes.hpp"
#include "Image.hpp"
#include "Utils.hpp"
#include "FileParser.hpp"
#include "ClusterCmdArgs.hpp"
#include "Cluster.hpp"
#include "ClusterAlgorithms.hpp"

int main(int argc, char const *argv[])
{
    ClusterCmdArgs args(argc, argv);

    FileParser inputParser(args.inputFile);

    const std::vector<ImagePtr> input_images = inputParser.GetImages();
    std::vector<Cluster> clusters;
    int cluster_id_formatter = (int)std::to_string(args.number_of_clusters).length();
    int size_formatter = (int)std::to_string(input_images.size()).length();
    if (args.method == "Classic")
        clusters = LloydsAssignment(input_images, args.number_of_clusters);
    else if (args.method == "LSH")
        ;
    else if (args.method == "Hypercube")
        ;
    else
    {
        std::cout << "Error, unknown method" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<double> silhouettes; // = Silhouettes(clusters);
    int total = 0;
    for (auto cluster : clusters)
    {
        std::cout << "CLUSTER-" << std::setw(cluster_id_formatter)
                  << cluster.GetClusterId() + 1 << " {size: "
                  << std::setw(size_formatter)
                  << cluster.GetMemberOfCluster().size() << ", centroid: "
                  << cluster.GetCentroid().id << "}" << std::endl;
        total += cluster.GetMemberOfCluster().size();
    }
    std::cout << "TOTAL ELEMENTS: " << total << std::endl;
    std::cout << "\nclustering_time: " << std::endl;
    std::cout << "\nSilhouette: [";
    for (auto silhouette : silhouettes)
        std::cout << silhouette << ", ";
    // for to print silhouette, needs to be done
    std::cout << "]" << std::endl
              << std::endl;
    if (args.complete)
        for (auto cluster : clusters)
        {
            std::cout << "CLUSTER-" << std::setw(cluster_id_formatter)
                      << cluster.GetClusterId() + 1 << " {"
                      << cluster.GetCentroid().id;
            for (auto image : cluster.GetMemberOfCluster())
                std::cout << ", " << image->id;
            std::cout << "}" << std::endl;
        }
    // std::ofstream output_file;
    // output_file.open(args.outputFile);
    // output_file.close();
    return EXIT_SUCCESS;
}
