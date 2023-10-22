#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <tuple>

#include "BruteForce.hpp"
#include "CubeCmdArgs.hpp"
#include "Cube.hpp"
#include "FileParser.hpp"
#include "Utils.hpp"

int main(int argc, char const *argv[])
{
    CubeCmdArgs args(argc, argv);

    readFilenameIfEmpty(args.inputFile, "input");
    FileParser inputParser(args.inputFile);

    const std::vector<ImagePtr> input_images = inputParser.GetImages();

    readFilenameIfEmpty(args.queryFile, "query");

    readFilenameIfEmpty(args.outputFile, "output");
    std::ofstream output_file;

    int w = 4;
    int numBuckets = std::pow(2, args.dimension);

    Cube cube(input_images, w, args.dimension, args.maxCanditates, args.probes, args.numNn, numBuckets);

    while (true)
    {
        if (args.queryFile == "exit")
            break;

        FileParser queryParser(args.queryFile);
        std::vector<ImagePtr> query_images = queryParser.GetImages();

        output_file.open(args.outputFile);

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
