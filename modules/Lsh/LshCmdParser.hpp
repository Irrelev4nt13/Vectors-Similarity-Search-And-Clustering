#pragma once

#include <cstring>
#include <Lsh.hpp>

class LshCmdArgs
{
public:
    std::string inputFile = "";  // -d <input file>
    std::string queryFile = "";  // -q <query file>
    std::string outputFile = ""; // -o <output file>
    int numHashFuncs = 4;        // –k number of hash functions
    int numHtables = 5;          // -L number of hash tables
    int numNn = 1;               // -Ν number of Nearest Neighbors
    double radius = 10000;       // -R radius
};

class LshCmdParser
{
private:
    LshCmdArgs args;

public:
    LshCmdParser(const int argc, const char *argv[])
    {
        for (int i = 0; i < argc; i++)
        {
            if (!strcmp(argv[i], "-d"))
                args.inputFile = std::string(argv[i + 1]);
            else if (!strcmp(argv[i], "-q"))
                args.queryFile = std::string(argv[i + 1]);
            else if (!strcmp(argv[i], "-k"))
                args.numHashFuncs = atoi(argv[i + 1]);
            else if (!strcmp(argv[i], "-L"))
                args.numHtables = atoi(argv[i + 1]);
            else if (!strcmp(argv[i], "-o"))
                args.outputFile = std::string(argv[i + 1]);
            else if (!strcmp(argv[i], "-N"))
                args.numNn = atoi(argv[i + 1]);
            else if (!strcmp(argv[i], "-R"))
                args.radius = atof(argv[i + 1]);
        }
    }

    ~LshCmdParser() {}

    inline const LshCmdArgs &GetLshArgs() const
    {
        return this->args;
    }
};