#include <iostream>
#include <Lsh.hpp>

Lsh::Lsh(const std::string &input_file,
         const std::string &query_file,
         const int &num_of_hash_functions,
         const int &num_of_hash_tables,
         const std::string &output_file,
         const int &num_of_nearest_neighbors,
         const double &radius)
    : input_file(input_file),
      query_file(query_file), num_of_hash_functions(num_of_hash_functions),
      num_of_hash_tables(num_of_hash_tables), output_file(output_file),
      num_of_nearest_neighbors(num_of_nearest_neighbors),
      radius(radius) {}
Lsh::~Lsh() {}