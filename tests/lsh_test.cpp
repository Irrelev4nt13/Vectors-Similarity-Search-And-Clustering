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
    int numHashFuncs;
    int numHtables;
    int numNn;
    std::string inputFile;
    std::string queryFile;
    int w;
    double threshold;
    int count = 0;
    int totals = 0;

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-d"))
            inputFile = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-q"))
            queryFile = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-k"))
            numHashFuncs = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-L"))
            numHtables = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-N"))
            numNn = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-w"))
            w = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-t"))
            threshold = atof(argv[i + 1]);
    }

    LshCmdArgs args(argc, argv);

    FileParser inputParser(inputFile);
    const std::vector<ImagePtr> input_images = inputParser.GetImages();

    FileParser queryParser(queryFile);
    std::vector<ImagePtr> query_images = queryParser.GetImages();

    int numBuckets = inputParser.GetMetadata().numOfImages / 8;

    ImageDistance::setMetric(DistanceMetric::EUCLIDEAN);

    Lsh lsh(input_images, numHashFuncs, numHtables, numNn, w, numBuckets);

    for (int q = 0; q < 10; q++)
    {
        ImagePtr query = query_images[q];

        std::vector<Neighbor> approx_vector = lsh.Approximate_kNN(query);

        std::vector<Neighbor> brute_vector = BruteForce(input_images, query, numNn);

        int limit = approx_vector.size();

        for (int i = 0; i < limit; i++)
        {
            ImagePtr image = approx_vector[i].image;
            double dist = approx_vector[i].distance;
            std::cout << "Nearest neighbor-" << i + 1 << ": " << image->id << std::endl
                      << "distanceLSH: " << dist << "\n";

            dist = brute_vector[i].distance;
            std::cout << "distanceTrue: " << dist << "\n\n";
            dist = brute_vector[i].distance;
            if (approx_vector[i].distance / brute_vector[i].distance > 1.0 && approx_vector[i].distance / brute_vector[i].distance <= threshold)
                count++;
        }
        totals += brute_vector.size();
    }
    double percentage = (static_cast<double>(count) / totals) * 100.0;

    std::cout << percentage << std::endl;
    // std::cout << "AproxPercentage: " << percentage << "%" << std::endl;
    return EXIT_SUCCESS;
}