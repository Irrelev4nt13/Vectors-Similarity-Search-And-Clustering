#include <iostream>
#include <vector>

#include <Lsh.hpp>
#include <LshCmdParser.hpp>
#include <Utils.hpp>

#include <BruteForce.hpp>

int main(int argc, char const *argv[])
{
    LshCmdParser parser(argc, argv);

    LshCmdArgs args = parser.GetLshArgs();

    // Check if the input is empty in order to ask for it in the main
    FileParser inputParser(args.inputFile);

    const std::vector<Image> input_images = inputParser.GetImages();

    // Check if the query is empty in order to ask for it in the main
    FileParser queryParser(args.queryFile);

    const std::vector<Image> query_images = queryParser.GetImages();

    int w = 5;
    int numBuckets = inputParser.GetMetadata().numOfImages / 8;

    Lsh lsh(input_images, args.numHashFuncs, args.numHtables, args.numNn, args.radius, w, numBuckets);

    // while (true)
    // {
    // Replace by a for to parse all queries
    const Image &query = query_images[0];

    // std::vector<std::tuple<Image, double>> brute_vector = BruteForce(input_images, query, args.numNn);

    // std::cout << "Query Image: " << query.id << std::endl;
    // for (const auto &tuple : brute_vector)
    // {
    //     double dist = std::get<1>(tuple);
    //     const Image &image = std::get<0>(tuple);
    //     std::cout << "ImageID: " << image.id << "\tDistance: " << dist << "\n";
    // }

    // }
    return EXIT_SUCCESS;
}
