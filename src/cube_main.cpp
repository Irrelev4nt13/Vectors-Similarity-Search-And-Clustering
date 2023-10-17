#include <iostream>
#include <fstream>
#include <chrono>

#include "BruteForce.hpp"
#include "CubeCmdArgs.hpp"
#include "Cube.hpp"
#include "FileParser.hpp"
#include "Utils.hpp"

int main(int argc, char const *argv[])
{
    CubeCmdArgs args(argc, argv);

    readFilenameIfEmpty(args.inputFile);
    FileParser inputParser(args.inputFile);

    const std::vector<ImagePtr> input_images = inputParser.GetImages();

    readFilenameIfEmpty(args.queryFile);
    FileParser queryParser(args.queryFile);

    const std::vector<ImagePtr> query_images = queryParser.GetImages();

    readFilenameIfEmpty(args.outputFile);
    std::ofstream output_file;
    output_file.open(args.outputFile);

    int w = 4;

    Cube cube(input_images, w, args.dimension, args.maxCanditates, args.probes, args.numNn, args.radius);
    // for (int i = 0; i < 10; i++)
    // {
    //     Image *query = query_images[i];

    //     auto begin_cube = std::chrono::high_resolution_clock::now();
    //     std::vector<std::tuple<Image *, double>> aprox_vector = cube.Approximate_kNN(query);
    //     auto end_cube = std::chrono::high_resolution_clock::now();
    //     auto elapsed_cube = std::chrono::duration_cast<std::chrono::nanoseconds>(end_cube - begin_cube);

    //     auto begin_brute = std::chrono::high_resolution_clock::now();
    //     std::vector<std::tuple<Image *, double>> brute_vector = BruteForce(input_images, query, args.numNn);
    //     auto end_brute = std::chrono::high_resolution_clock::now();
    //     auto elapsed_brute = std::chrono::duration_cast<std::chrono::nanoseconds>(end_brute - begin_brute);

    //     output_file << "Query: " << query->id << std::endl;
    //     // for (auto &tuple : aprox_vector)
    //     int limit = aprox_vector.size();
    //     for (int i = 0; i < limit; i++)
    //     {
    //         double dist = std::get<1>(aprox_vector[i]);
    //         Image *image = std::get<0>(aprox_vector[i]);
    //         output_file << "Nearest neighbor-" << i + 1 << ": " << image->id << std::endl
    //                     << "distanceHypercube: " << dist << "\n";
    //         dist = std::get<1>(brute_vector[i]);
    //         output_file << "distanceTrue: " << dist << "\n";
    //     }
    //     output_file << "tHypercube: " << elapsed_cube.count() * 1e-9 << std::endl;
    //     output_file << "tTrue: " << elapsed_brute.count() * 1e-9 << std::endl;
    //     // std::vector<Image *> range_vector = cube.Approximate_Range_Search(query);
    //     output_file << "R-near neighbors:" << std::endl;
    //     // for (auto &image : range_vector)
    //     //     // output_file << "ImageID: " <<
    //     //     output_file << image->id << std::endl;

    //     output_file << std::endl;
    // }
    // output_file.close();

    return EXIT_SUCCESS;
}
