#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

#include "Image.hpp"
#include "Utils.hpp"
#include "Lsh.hpp"
#include "LshCmdArgs.hpp"
#include "FileParser.hpp"
#include "BruteForce.hpp"

int main(int argc, char const *argv[])
{
    LshCmdArgs args(argc, argv);

    readFilenameIfEmpty(args.inputFile, "input");
    FileParser inputParser(args.inputFile);

    const std::vector<ImagePtr> input_images = inputParser.GetImages();

    readFilenameIfEmpty(args.queryFile, "query");

    readFilenameIfEmpty(args.outputFile, "output");
    std::ofstream output_file;

    int w = 4;
    int numBuckets = inputParser.GetMetadata().numOfImages / 8;

    Lsh lsh(input_images, args.numHashFuncs, args.numHtables, args.numNn, args.radius, w, numBuckets);

    while (true)
    {
        FileParser queryParser(args.queryFile);
        std::vector<ImagePtr> query_images = queryParser.GetImages();

        if (args.queryFile == "exit")
            break;

        output_file.open(args.outputFile);

        // for (const Image &query : query_images){

        // }
        for (int i = 0; i < 10; i++)
        {
            ImagePtr query = query_images[i];

            startClock();
            std::vector<Neighbor> aprox_vector = lsh.Approximate_kNN(query);
            auto elapsed_lsh = stopClock();

            startClock();
            std::vector<Neighbor> brute_vector = BruteForce(input_images, query, args.numNn);
            auto elapsed_brute = stopClock();

            output_file << "Query: " << query->id << std::endl;

            std::cout << "calculating" << std::endl;

            int limit = aprox_vector.size();
            for (int i = 0; i < limit; i++)
            {
                ImagePtr image;
                double dist;
                std::tie(image, dist) = aprox_vector[i];

                output_file << "Nearest neighbor-" << i + 1 << ": " << image->id << std::endl
                            << "distanceLSH: " << dist << "\n";

                dist = std::get<1>(brute_vector[i]);
                output_file << "distanceTrue: " << dist << "\n";
            }

            output_file << "tLSH: " << elapsed_lsh.count() * 1e-9 << std::endl;
            output_file << "tTrue: " << elapsed_brute.count() * 1e-9 << std::endl;

            std::vector<ImagePtr> range_vector = lsh.Approximate_Range_Search(query);

            output_file << "R-near neighbors:" << std::endl;
            for (auto &image : range_vector)
                output_file << "ImageID: " << image->id << std::endl;

            output_file << std::endl;

            // Read new query and output files.
            args.queryFile.clear();
            readFilenameIfEmpty(args.queryFile, "query");

            args.outputFile.clear();
            readFilenameIfEmpty(args.outputFile, "output");
        }

        output_file.close();
    }

    return EXIT_SUCCESS;
}
