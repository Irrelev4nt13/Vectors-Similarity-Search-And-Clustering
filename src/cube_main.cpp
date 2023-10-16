#include <iostream>
#include <fstream>

#include "CubeCmdArgs.hpp"
#include "Cube.hpp"
#include "FileParser.hpp"
#include "Utils.hpp"

int main(int argc, char const *argv[])
{
    CubeCmdArgs args(argc, argv);

    // Check if the input is empty in order to ask for it in the main
    if (args.inputFile.empty())
    {
        std::cout << "Enter input file: ";
        std::getline(std::cin, args.inputFile);
    }
    FileParser inputParser(args.inputFile);

    const std::vector<ImagePtr> input_images = inputParser.GetImages();

    // Check if the query is empty in order to ask for it in the main
    if (args.queryFile.empty())
    {
        std::cout << "Enter query file: ";
        std::getline(std::cin, args.queryFile);
    }
    FileParser queryParser(args.queryFile);

    const std::vector<ImagePtr> query_images = queryParser.GetImages();

    // std::fstream output_file()
    if (args.outputFile.empty())
    {
        std::cout << "Enter output file: ";
        std::getline(std::cin, args.outputFile);
    }
    std::ofstream output_file;
    output_file.open(args.outputFile);

    int w = 4;

    Cube cube(input_images, w, args.dimension, args.maxCanditates, args.probes, args.numNn, args.radius);

    cube.print_cube();

    return EXIT_SUCCESS;
}
