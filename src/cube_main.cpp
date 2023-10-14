#include <iostream>

#include "CubeCmdArgs.hpp"
#include "Cube.hpp"
#include "Utils.hpp"

int main(int argc, char const *argv[])
{
    CubeCmdArgs args(argc, argv);

    Cube cube(args.dimension, args.maxCanditates, args.probes, args.numNn, args.radius);

    cube.print_cube();

    return EXIT_SUCCESS;
}
