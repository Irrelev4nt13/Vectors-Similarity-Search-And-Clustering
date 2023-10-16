#ifndef CLUSTERCMDARGS_HPP_
#define CLUSTERCMDARGS_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

class ClusterCmdArgs
{
public:
    std::string inputFile;  // -d <input file>
    std::string configFile; // -c <configuration file>
    std::string outputFile; // -o <output file>
    bool complete;          // -complete <optional>
    std::string method;     //  -m <method> (Values are: Classic | LSH | Hypercube)

    int number_of_clusters;              // K of K-medians
    int number_of_vector_hash_tables;    // default: L=3
    int number_of_vector_hash_functions; // k of LSH for vectors, default: 4
    int max_number_M_hypercube;          // M of Hypercube, default: 10
    int number_of_hypercube_dimensions;  // k of Hypercube, default: 3
    int number_of_probes;                // probes of Hypercube, default: 2

    ClusterCmdArgs(const int argc, const char *argv[]) : inputFile(""),
                                                         configFile(""),
                                                         outputFile(""),
                                                         complete(false),
                                                         method(""),
                                                         number_of_vector_hash_tables(3),
                                                         number_of_vector_hash_functions(4),
                                                         max_number_M_hypercube(10),
                                                         number_of_hypercube_dimensions(3),
                                                         number_of_probes(2)
    {
        for (int i = 0; i < argc; i++)
        {
            if (!strcmp(argv[i], "-i"))
                inputFile = std::string(argv[i + 1]);
            else if (!strcmp(argv[i], "-c"))
                configFile = std::string(argv[i + 1]);
            else if (!strcmp(argv[i], "-o"))
                outputFile = std::string(argv[i + 1]);
            else if (!strcmp(argv[i], "-complete"))
                complete = true;
            else if (!strcmp(argv[i], "-m"))
                method = std::string(argv[i + 1]);
        }

        if (inputFile.empty() || configFile.empty() || outputFile.empty() || method.empty())
        {
            std::string emptyVar = (inputFile.empty() ? "input file" : configFile.empty() ? "config file"
                                                                   : outputFile.empty()   ? "output file"
                                                                                          : "method");
            std::cout << "Error, " << emptyVar << " was not given" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::fstream conf(configFile, std::ios::in);
        if (conf.fail())
        {
            std::cerr << "Failed to open the file." << std::endl;
            conf.close();
            exit(EXIT_FAILURE);
        }

        bool cluster_was_given = false;
        std::string line;

        while (std::getline(conf, line))
        {
            if (line.empty())
                continue;

            std::string arg, val;
            std::stringstream ss(line);
            std::getline(ss, arg, ':');
            ss >> val;

            if (arg == "number_of_clusters")
            {
                number_of_clusters = std::stoi(val);
                cluster_was_given = true;
            }
            else if (arg == "number_of_vector_hash_tables")
                number_of_vector_hash_tables = std::stoi(val);
            else if (arg == "number_of_vector_hash_functions")
                number_of_vector_hash_functions = std::stoi(val);
            else if (arg == "max_number_M_hypercube")
                max_number_M_hypercube = std::stoi(val);
            else if (arg == "number_of_hypercube_dimensions")
                number_of_hypercube_dimensions = std::stoi(val);
            else if (arg == "number_of_probes")
                number_of_probes = std::stoi(val);
        }
        if (!cluster_was_given)
        {
            std::cerr << "Error, number K of cluster was not given" << std::endl;
            conf.close();
            exit(EXIT_FAILURE);
        }

        conf.close();
    }
};

#endif