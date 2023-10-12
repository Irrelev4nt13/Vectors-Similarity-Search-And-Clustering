#include <iostream>
#include <vector>

#include <Lsh.hpp>
#include <LshCmdParser.hpp>
#include <Utils.hpp>

int main(int argc, char const *argv[])
{
    LshCmdParser parser(argc, argv);

    LshCmdArgs args = parser.GetLshArgs();

    FileParser fileParser(args.inputFile);

    Metadata metadata = fileParser.GetMetadata();
    std::vector<Image> images = fileParser.GetImages();

    Lsh lsh(images, args.numHashFuncs, args.numHtables, args.numNn, args.radius);

    lsh.solve();

    return 0;
}
