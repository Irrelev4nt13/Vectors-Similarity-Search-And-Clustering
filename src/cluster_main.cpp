#include <iostream>
#include <fstream>

#include "Image.hpp"
#include "FileParser.hpp"
#include "ClusterCmdArgs.hpp"
#include "Cluster.hpp"
#include "ClusterAlgorithms.hpp"

int main(int argc, char const *argv[])
{
    ClusterCmdArgs args(argc, argv);

    FileParser inputParser(args.inputFile);

    const std::vector<Image *> input_images = inputParser.GetImages();

    if (args.method == "Classic")
        std::vector<Cluster> clusters_kmeans = KMeansPlusPlus(input_images, args.number_of_clusters);
    else if (args.method == "LSH")
        ;
    else if (args.method == "Hypercube")
        ;
    else
    {
        std::cout << "Error, unknown method" << std::endl;
        exit(EXIT_FAILURE);
    }

    // std::ofstream output_file;
    // output_file.open(args.outputFile);
    // output_file.close();
    return EXIT_SUCCESS;
}
