#include <iostream>
#include <Cluster.hpp>

Cluster::Cluster(const std::string &input_file,
                 const std::string &configuration_file,
                 const std::string &output_file,
                 const bool &complete,
                 const std::string &method)
    : input_file(input_file),
      configuration_file(configuration_file),
      output_file(output_file),
      complete(complete),
      method(method) {}
Cluster::~Cluster() {}