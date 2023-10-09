#include <iostream>

#include <Cluster.hpp>
#include <Utils.hpp>

int main(int argc, char const *argv[])
{
    std::string input_file;
    std::string configuration_file;
    std::string output_file;
    bool complete;
    std::string method;
    split_cluster_args(argc, argv, input_file, configuration_file, output_file, complete, method);
    Cluster *cluster = new Cluster(input_file,
                                   configuration_file,
                                   output_file,
                                   complete,
                                   method);
    cluster->print_cluster();
    delete cluster;
    return 0;
}
