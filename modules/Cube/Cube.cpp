#include <iostream>
#include <Cube.hpp>

Cube::Cube(const CubeArgs &args)
    : input_file(args.input_file),
      query_file(args.query_file),
      dimension(args.dimension),
      max_candidates(args.max_candidates),
      probes(args.probes),
      output_file(args.output_file),
      num_of_nearest_neighbors(args.num_of_nearest_neighbors),
      radius(args.radius) {}
Cube::~Cube() {}

void Cube::print_cube()
{
    std::cout << input_file << std::endl;
    std::cout << query_file << std::endl;
    std::cout << dimension << std::endl;
    std::cout << max_candidates << std::endl;
    std::cout << probes << std::endl;
    std::cout << output_file << std::endl;
    std::cout << num_of_nearest_neighbors << std::endl;
    std::cout << radius << std::endl;
}