#include <iostream>

#include <Lsh.hpp>
#include <Utils.hpp>

int main(int argc, char const *argv[])
{
    LshArgs lshArgs = LshArgs();
    split_lsh_args(argc, argv, lshArgs);
    Lsh *lsh = new Lsh(lshArgs);
    lsh->print_lsh();
    delete lsh;
    return 0;
}
