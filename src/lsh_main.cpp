#include <iostream>
#include <vector>

#include "Lsh.hpp"
#include "LshCmdArgs.hpp"
#include "FileParser.hpp"
#include "BruteForce.hpp"

int main(int argc, char const *argv[])
{
    LshCmdArgs args(argc, argv);

    // Check if the input is empty in order to ask for it in the main
    FileParser inputParser(args.inputFile);

    const std::vector<Image *> input_images = inputParser.GetImages();

    // Check if the query is empty in order to ask for it in the main
    FileParser queryParser(args.queryFile);

    const std::vector<Image *> query_images = queryParser.GetImages();

    int w = 4;
    int numBuckets = inputParser.GetMetadata().numOfImages / 16;

    Lsh lsh(input_images, args.numHashFuncs, args.numHtables, args.numNn, args.radius, w, numBuckets);

    for (int i = 0; i < 10; i++)
    // for (const Image &query : query_images)
    {
        Image *query = query_images[i];

        // Image *query = query_images[0];

        std::vector<std::tuple<Image *, double>> brute_vector = BruteForce(input_images, *query, args.numNn);

        std::cout << "Query Image: " << query->id << std::endl;
        for (auto tuple : brute_vector)
        {
            double dist = std::get<1>(tuple);
            Image *image = std::get<0>(tuple);
            std::cout << "ImageID: " << image->id << "\tBrute_Distance: " << dist << "\n";
        }

        std::vector<std::tuple<Image *, double>> aprox_vector = lsh.Approximate_kNN(query);

        // std::cout << "Query Image: " << query.id << std::endl;
        for (auto &tuple : aprox_vector)
        {
            double dist = std::get<1>(tuple);
            Image *image = std::get<0>(tuple);
            std::cout << "ImageID: " << image->id << "\tAprox_Distance: " << dist << "\n";
        }

        std::vector<Image *> range_vector = lsh.Approximate_Range_Search(query);
        std::cout << "Range Search" << std::endl;
        for (auto &image : range_vector)
        {
            std::cout << "ImageID: " << image->id << "\n";
        }

        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
