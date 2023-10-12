#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include <Lsh.hpp>
#include <LshCmdParser.hpp>
#include <Utils.hpp>

int main(int argc, char const *argv[])
{
    LshCmdParser parser(argc, argv);

    LshCmdArgs args = parser.GetLshArgs();

    Lsh *lsh = new Lsh(args.numHashFuncs, args.numHtables, args.numNn, args.radius);

    Metadata metadata = Metadata();
    std::vector<std::vector<char>> *images = new std::vector<std::vector<char>>;
    parseInputFile(args.inputFile, metadata, *images);

    delete images;
    delete lsh;
    return 0;
}
