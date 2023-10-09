#include <iostream>
#include <Cluster.hpp>

Cluster::Cluster(const ClusterArgs &args)
    : input_file(args.input_file),
      configuration_file(args.configuration_file),
      output_file(args.output_file),
      complete(args.complete),
      method(args.method) {}
Cluster::~Cluster() {}

void Cluster::print_cluster()
{
    std::cout << input_file << std::endl;
    std::cout << configuration_file << std::endl;
    std::cout << output_file << std::endl;
    std::cout << std::boolalpha;
    std::cout << complete << std::endl;
    std::cout << method << std::endl;
}