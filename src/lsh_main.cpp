#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include <Lsh.hpp>
#include <Utils.hpp>

int main(int argc, char const *argv[])
{
    LshArgs lshArgs = LshArgs();
    split_lsh_args(argc, argv, lshArgs);
    Lsh *lsh = new Lsh(lshArgs);

    Metadata metadata = Metadata();
    std::vector<std::vector<char>> *images = new std::vector<std::vector<char>>;
    parseInputFile(lshArgs.input_file, metadata, *images);

    delete images;
    delete lsh;
    return 0;
}

// We need to implement the following:
// Lsh me metrikh L2 ston d-space
//      prepei omos na dinete parametropoihsei oste na xrhsimopoihthei
//      kai me allh metrikh kai se allh diastash eukola

// Πρέπει να επιστρέφει
//      α) Πλησιεστερο γειτονα
//      β) τους Ν πλησιεστερους γειτονες
//      γ) τα διανυσματα εντος ακτινας R απο το q