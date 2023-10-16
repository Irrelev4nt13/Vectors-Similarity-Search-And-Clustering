#include <iostream>
#include <fstream>

#include "CubeCmdArgs.hpp"
#include "Cube.hpp"
#include "FileParser.hpp"
#include "Utils.hpp"

void readFilenameIfEmpty(std::string &filename)
{
    std::cout << "Enter " << filename << " file: ";
    std::getline(std::cin, filename);
}

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

    cube.print_cube();

    return EXIT_SUCCESS;
}
