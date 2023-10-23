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
#include "Lsh.hpp"
#include "Cube.hpp"

int main(int argc, char const *argv[])
{
    ClusterCmdArgs args(argc, argv);

    FileParser inputParser(args.inputFile);

    const std::vector<ImagePtr> input_images = inputParser.GetImages();
    std::vector<Cluster> clusters;
    int cluster_id_formatter = (int)std::to_string(args.number_of_clusters).length();
    int size_formatter = (int)std::to_string(input_images.size()).length();
    ImageDistance::setMetric(DistanceMetric::EUCLIDEAN);
    std::chrono::nanoseconds elapsed_cluster;
    if (args.method == "Classic")
    {
        startClock();
        clusters = LloydsAssignment(input_images, args.number_of_clusters);
        elapsed_cluster = stopClock();
    }
    else if (args.method == "LSH")
    {
        int w = 4;
        int numBuckets = inputParser.GetMetadata().numOfImages / 8;
        Lsh lsh(input_images, args.number_of_vector_hash_functions, args.number_of_vector_hash_tables, -1, w, numBuckets);

        startClock();
        clusters = ReverseRangeSearchLSH(input_images, lsh, args.number_of_clusters);
        elapsed_cluster = stopClock();
    }
    else if (args.method == "Hypercube")
    {
        int w = 4;
        int numBuckets = std::pow(2, args.number_of_hypercube_dimensions);
        Cube cube(input_images, w, args.number_of_hypercube_dimensions, args.max_number_M_hypercube, args.number_of_probes, -1, numBuckets);

        startClock();
        clusters = ReverseRangeSearchHyperCube(input_images, cube, args.number_of_clusters);
        elapsed_cluster = stopClock();
    }
    else
    {
        std::cout << "Error, unknown method" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::tuple<std::vector<double>, double> silhouettes = Silhouettes(clusters);
    for (auto cluster : clusters)
        std::cout << "CLUSTER-" << std::setw(cluster_id_formatter)
                  << cluster.GetClusterId() + 1 << " {size: "
                  << std::setw(size_formatter)
                  << cluster.GetMemberOfCluster().size() << ", centroid: "
                  << cluster.GetCentroid()->id << "}" << std::endl;

    std::cout << "\nclustering_time: " << elapsed_cluster.count() * 1e-9 << std::endl;
    std::cout << "\nSilhouette: [";
    for (auto silhouette : std::get<0>(silhouettes))
        std::cout << silhouette << ", ";

    std::cout << std::get<1>(silhouettes) << "]" << std::endl
              << std::endl;
    if (args.complete)
        for (auto cluster : clusters)
        {
            std::cout << "CLUSTER-" << std::setw(cluster_id_formatter)
                      << cluster.GetClusterId() + 1 << " {"
                      << cluster.GetCentroid()->id;
            for (auto image : cluster.GetMemberOfCluster())
                std::cout << ", " << image->id;
            std::cout << "}" << std::endl;
        }
    // std::ofstream output_file;
    // output_file.open(args.outputFile);
    // output_file.close();
    return EXIT_SUCCESS;
}
