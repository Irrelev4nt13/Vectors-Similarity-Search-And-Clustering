#include <iostream>

#include <Cube.hpp>
#include <Utils.hpp>

int main(int argc, char const *argv[])
{
    std::string input_file;
    std::string query_file;
    int dimension;
    int max_candidates;
    int probes;
    std::string output_file;
    int num_of_nearest_neighbors;
    double radius;
    split_cube_args(argc, argv,
                    input_file,
                    query_file,
                    dimension,
                    max_candidates,
                    probes,
                    output_file,
                    num_of_nearest_neighbors,
                    radius);
    Cube *cube = new Cube(input_file,
                          query_file,
                          dimension,
                          max_candidates,
                          probes,
                          output_file,
                          num_of_nearest_neighbors,
                          radius);
    cube->print_cube();
    delete cube;
    return 0;
}
