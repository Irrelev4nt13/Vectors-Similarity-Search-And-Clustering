#include <iostream>
#include <vector>
#include <fstream>

#include "Image.hpp"
#include "Utils.hpp"
#include "Lsh.hpp"
#include "LshCmdArgs.hpp"
#include "FileParser.hpp"
#include "BruteForce.hpp"
#include "ImageDistance.hpp"

int main(int argc, char const *argv[])
{
    LshCmdArgs args(argc, argv);

    readFilenameIfEmpty(args.inputFile, "input");
    FileParser inputParser(args.inputFile);

    const std::vector<ImagePtr> input_images = inputParser.GetImages();

    readFilenameIfEmpty(args.queryFile, "query");

    if (args.queryFile == "exit")
        return EXIT_SUCCESS;

    readFilenameIfEmpty(args.outputFile, "output");
    std::ofstream output_file;

    int w = 4;
    int numBuckets = inputParser.GetMetadata().numOfImages / 8;

    ImageDistance::setMetric(DistanceMetric::EUCLIDEAN);

    Lsh lsh(input_images, args.numHashFuncs, args.numHtables, args.numNn, w, numBuckets);

    while (true)
    {
        FileParser queryParser(args.queryFile);
        std::vector<ImagePtr> query_images = queryParser.GetImages();

        output_file.open(args.outputFile);

        for (int q = 0; q < 10; q++)
        {
            ImagePtr query = query_images[q];

            startClock();
            std::vector<Neighbor> approx_vector = lsh.Approximate_kNN(query);
            auto elapsed_lsh = stopClock();

            startClock();
            std::vector<Neighbor> brute_vector = BruteForce(input_images, query, args.numNn);
            auto elapsed_brute = stopClock();

            output_file << "Query: " << query->id << std::endl;

            int limit = approx_vector.size();
            for (int i = 0; i < limit; i++)
            {
                ImagePtr image = approx_vector[i].image;
                double dist = approx_vector[i].distance;

                output_file << "Nearest neighbor-" << i + 1 << ": " << image->id << std::endl
                            << "distanceLSH: " << dist << "\n";

                dist = brute_vector[i].distance;
                output_file << "distanceTrue: " << dist << "\n";
            }

            output_file << "tLSH: " << elapsed_lsh.count() * 1e-9 << std::endl;
            output_file << "tTrue: " << elapsed_brute.count() * 1e-9 << std::endl;

            std::vector<ImagePtr> range_vector = lsh.Approximate_Range_Search(query, args.radius);

            output_file << "R-near neighbors:" << std::endl;
            limit = range_vector.size();
            for (int i = 0; i < limit; i++)
                output_file << range_vector[i]->id << std::endl;

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
