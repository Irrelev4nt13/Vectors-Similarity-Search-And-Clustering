#include <iostream>
#include <vector>
#include <fstream>

#include "Lsh.hpp"
#include "LshCmdArgs.hpp"
#include "FileParser.hpp"
#include "BruteForce.hpp"

int main(int argc, char const *argv[])
{
    LshCmdArgs args(argc, argv);

    // Check if the input is empty in order to ask for it in the main
    if (args.inputFile.empty())
    {
        std::cout << "Enter input file: ";
        std::getline(std::cin, args.inputFile);
    }
    FileParser inputParser(args.inputFile);

    const std::vector<Image *> input_images = inputParser.GetImages();

    // Check if the query is empty in order to ask for it in the main
    if (args.queryFile.empty())
    {
        std::cout << "Enter query file: ";
        std::getline(std::cin, args.queryFile);
    }
    FileParser queryParser(args.queryFile);

    const std::vector<Image *> query_images = queryParser.GetImages();

    // std::fstream output_file()
    if (args.outputFile.empty())
    {
        std::cout << "Enter output file: ";
        std::getline(std::cin, args.outputFile);
    }
    std::ofstream output_file;
    output_file.open(args.outputFile);

    int w = 4;
    int numBuckets = inputParser.GetMetadata().numOfImages / 8;

    Lsh lsh(input_images, args.numHashFuncs, args.numHtables, args.numNn, args.radius, w, numBuckets);
    // while (true)
    // {
    // for (const Image &query : query_images)
    for (int i = 0; i < 10; i++)
    {
        Image *query = query_images[i];

        std::vector<std::tuple<Image *, double>> aprox_vector = lsh.Approximate_kNN(query);
        std::vector<std::tuple<Image *, double>> brute_vector = BruteForce(input_images, query, args.numNn);

        output_file << "Query: " << query->id << std::endl;
        // for (auto &tuple : aprox_vector)
        int limit = aprox_vector.size();
        for (int i = 0; i < limit; i++)
        {
            double dist = std::get<1>(aprox_vector[i]);
            Image *image = std::get<0>(aprox_vector[i]);
            output_file << "Nearest neighbor-" << i + 1 << ": " << image->id << std::endl
                        << "distanceLSH: " << dist << "\n";
            dist = std::get<1>(brute_vector[i]);
            output_file << "distanceTrue: " << dist << "\n";
        }
        output_file << "tLSH: " << std::endl;
        output_file << "tTrue: " << std::endl;
        // std::vector<Image *> range_vector = lsh.Approximate_Range_Search(query);
        output_file << "R-near neighbors:" << std::endl;
        // for (auto &image : range_vector)
        //     // output_file << "ImageID: " <<
        //     output_file << image->id << std::endl;

        output_file << std::endl;
    }
    output_file.close();
    // for (auto query : query_images)
    //     delete query;

    // std::cout << "\nEnter new query file, type exit to stop: ";
    // std::getline(std::cin, args.queryFile);

    // if (args.queryFile == "exit")
    //     break;
    // else
    //     queryParser(args.queryFile);
    // }

    return EXIT_SUCCESS;
}
