#include <iostream>
#include <cstring>
#include <Utils.hpp>
#include <sstream>
#include <fstream>
#include <string>

void split_lsh_args(const int argc, const char *argv[], LshArgs &args)
{
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-d"))
            args.input_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-q"))
            args.query_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-k"))
            args.num_of_hash_functions = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-L"))
            args.num_of_hash_tables = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-o"))
            args.output_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-N"))
            args.num_of_nearest_neighbors = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-R"))
            args.radius = atof(argv[i + 1]);
    }
}

void split_cube_args(const int argc, const char *argv[], CubeArgs &args)
{
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-d"))
            args.input_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-q"))
            args.query_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-k"))
            args.dimension = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-M"))
            args.max_candidates = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-probes"))
            args.probes = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-o"))
            args.output_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-N"))
            args.num_of_nearest_neighbors = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-R"))
            args.radius = atof(argv[i + 1]);
    }
}

void split_cluster_args(const int argc, const char *argv[], ClusterArgs &args)
{
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-i"))
            args.input_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-c"))
            args.configuration_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-o"))
            args.output_file = std::string(argv[i + 1]);
        else if (!strcmp(argv[i], "-complete"))
            args.complete = true;
        else if (!strcmp(argv[i], "-m"))
            args.method = std::string(argv[i + 1]);
    }
}

void parseInputFile(const std::string &inputFile, Metadata &metadata, char **images)
{
    std::ifstream file(inputFile);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        exit(1);
    }

    int magicNumber;

    // std::string magic;

    if (file >> magicNumber)
    {
        std::cout << "Read integer: " << magicNumber << std::endl;
    }
    else
    {
        std::cerr << "Failed to read an integer from the file." << std::endl;
    }

    // file.read(&magicNumber, 1);

    std::cout << "magic: " << magicNumber << std::endl;

    file.close();
}