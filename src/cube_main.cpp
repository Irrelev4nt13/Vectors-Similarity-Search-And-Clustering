#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

#include "BruteForce.hpp"
#include "CubeCmdArgs.hpp"
#include "Cube.hpp"
#include "FileParser.hpp"
#include "Utils.hpp"
#include "ImageDistance.hpp"

int main(int argc, char const *argv[])
{
    // Analyze arguments from command line and store them in a simple object
    CubeCmdArgs args(argc, argv);

    readFilenameIfEmpty(args.inputFile, "input");

    // Parse file and get the images
    FileParser inputParser(args.inputFile);
    const std::vector<ImagePtr> input_images = inputParser.GetImages();

    readFilenameIfEmpty(args.queryFile, "query");

    readFilenameIfEmpty(args.outputFile, "output");
    std::ofstream output_file;

    // window
    int w = 4;
    int numBuckets = std::pow(2, args.dimension); // {0,1}^d'=> 2^k

    // Configure the metric used for the lsh program
    ImageDistance::setMetric(DistanceMetric::EUCLIDEAN);

    // Initialize cube structure
    Cube cube(input_images, w, args.dimension, args.maxCanditates, args.probes, args.numNn, numBuckets);

    // Keep reading new query and output files until the user types "exit"
    while (true)
    {
        // Get query images
        FileParser queryParser(args.queryFile);
        std::vector<ImagePtr> query_images = queryParser.GetImages();

        output_file.open(args.outputFile);

        // For each query data point calculate its approximate k nearesest neighbors with hypercube algorithm and compare it to brute force
        // Also, make a range search with hypercube
        for (int q = 0; q < 10; q++)
        {
            ImagePtr query = query_images[q];

            startClock();
            std::vector<Neighbor> aprox_vector = cube.Approximate_kNN(query);
            auto elapsed_cube = stopClock();

            startClock();
            std::vector<Neighbor> brute_vector = BruteForce(input_images, query, args.numNn);
            auto elapsed_brute = stopClock();

            output_file << "Query: " << query->id << std::endl;

            int limit = aprox_vector.size();
            for (int i = 0; i < limit; i++)
            {
                ImagePtr image = aprox_vector[i].image;
                double dist = aprox_vector[i].distance;

                output_file << "Nearest neighbor-" << i + 1 << ": " << image->id << std::endl
                            << "distanceHypercube: " << dist << "\n";

                dist = brute_vector[i].distance;
                output_file << "distanceTrue: " << dist << "\n";
            }

            output_file << "tHypercube: " << elapsed_cube.count() * 1e-9 << std::endl;
            output_file << "tTrue: " << elapsed_brute.count() * 1e-9 << std::endl;

            std::vector<ImagePtr> range_vector = cube.Approximate_Range_Search(query, args.radius);

            output_file << "R-near neighbors:" << std::endl;
            for (auto &image : range_vector)
                output_file << image->id << std::endl;

            output_file << std::endl;
        }

        // Read new query and output files.
        args.queryFile.clear();
        std::cout << "Enter new query file, type exit to stop: ";
        std::getline(std::cin, args.queryFile);

        if (args.queryFile == "exit")
            break;

        args.outputFile.clear();
        readFilenameIfEmpty(args.outputFile, "output");

        output_file.close();
    }

    return EXIT_SUCCESS;
}
