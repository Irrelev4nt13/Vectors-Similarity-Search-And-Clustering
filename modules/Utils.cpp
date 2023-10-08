#include <iostream>
#include <cstring>
#include <Utils.hpp>

void split_lsh_args(const int argc, const char *argv[],
                    std::string &input_file,
                    std::string &query_file,
                    int &num_of_hash_functions,
                    int &num_of_hash_tables,
                    std::string &output_file,
                    int &num_of_nearest_neighbors,
                    double &radius)
{
    num_of_hash_functions = 4;
    num_of_hash_tables = 5;
    num_of_nearest_neighbors = 1;
    radius = 10000;
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-d"))
            input_file = argv[i + 1];
        else if (!strcmp(argv[i], "-q"))
            query_file = argv[i + 1];
        else if (!strcmp(argv[i], "-k"))
            num_of_hash_functions = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-L"))
            num_of_hash_tables = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-o"))
            output_file = argv[i + 1];
        else if (!strcmp(argv[i], "-N"))
            num_of_nearest_neighbors = atoi(argv[i + 1]);
        else if (!strcmp(argv[i], "-R"))
            radius = atof(argv[i + 1]);
    }
}
