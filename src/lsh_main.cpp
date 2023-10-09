#include <iostream>

#include <Lsh.hpp>
#include <Utils.hpp>

int main(int argc, char const *argv[])
{
    std::string input_file;
    std::string query_file;
    int num_of_hash_functions;
    int num_of_hash_tables;
    std::string output_file;
    int num_of_nearest_neighbors;
    double radius;
    split_lsh_args(argc, argv, input_file,
                   query_file,
                   num_of_hash_functions,
                   num_of_hash_tables,
                   output_file,
                   num_of_nearest_neighbors,
                   radius);
    Lsh *lsh = new Lsh(input_file,
                       query_file,
                       num_of_hash_functions,
                       num_of_hash_tables,
                       output_file,
                       num_of_nearest_neighbors,
                       radius);
    lsh->print_lsh();
    delete lsh;
    return 0;
}
