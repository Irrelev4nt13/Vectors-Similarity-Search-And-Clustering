#include <iostream>
#include <Lsh.hpp>

Lsh::Lsh(const LshArgs &args)
    : input_file(args.input_file),
      query_file(args.query_file),
      num_of_hash_functions(args.num_of_hash_functions),
      num_of_hash_tables(args.num_of_hash_tables),
      output_file(args.output_file),
      num_of_nearest_neighbors(args.num_of_nearest_neighbors),
      radius(args.radius) {}
Lsh::~Lsh() {}

void Lsh::print_lsh()
{
  std::cout << input_file << std::endl;
  std::cout << query_file << std::endl;
  std::cout << num_of_hash_functions << std::endl;
  std::cout << num_of_hash_tables << std::endl;
  std::cout << output_file << std::endl;
  std::cout << num_of_nearest_neighbors << std::endl;
  std::cout << radius << std::endl;
}