#include <iostream>
#include <Cube.hpp>

Cube::Cube(const std::string &input_file,
           const std::string &query_file,
           const int &dimension,
           const int &max_candidates,
           const int &probes,
           const std::string &output_file,
           const int &num_of_nearest_neighbors,
           const double &radius)
    : input_file(input_file),
      query_file(query_file),
      dimension(dimension),
      max_candidates(max_candidates),
      probes(probes),
      output_file(output_file),
      num_of_nearest_neighbors(num_of_nearest_neighbors),
      radius(radius) {}
Cube::~Cube() {}