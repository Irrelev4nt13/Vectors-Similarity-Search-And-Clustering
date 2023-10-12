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

    FileParser inputParser(args.inputFile);

    Metadata metadata_input = inputParser.GetMetadata();
    std::vector<Image> images_input = inputParser.GetImages();

    FileParser queryParser(args.queryFile);

    Metadata metadata_query = queryParser.GetMetadata();
    std::vector<Image> images_query = queryParser.GetImages();

    // Lsh lsh(images, args.numHashFuncs, args.numHtables, args.numNn, args.radius);
    std::vector<std::tuple<Image, double>> brute_vector = BruteForce(images_input, images_query[0], 3);
    // while (!brute_vector.empty())
    // {
    //     const std::tuple<Image, double> &neighbor = brute_vector.top();
    //     // std::cout << "ImageID: " << std::get<0>(neighbor).id << "\tDistance: " << std::get<1>(neighbor) << "\n";
    //     // neighbor.second.print();  // Uncomment if you have a print method for Image
    //     // nearestNeighbors.pop();
    // }
    // std::cout << "------------------\n";
    // }
    std::cout << "Query Image: " << images_query[0].id << std::endl;
    for (const auto &tuple : brute_vector)
    {
        double dist = std::get<1>(tuple);
        const Image &image = std::get<0>(tuple);
        std::cout << "ImageID: " << image.id << "\tDistance: " << dist << "\n";
    }
    return 0;
}
