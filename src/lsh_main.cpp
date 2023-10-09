// #include <iostream>

// #include <Lsh.hpp>
// #include <Utils.hpp>

// int main(int argc, char const *argv[])
// {
//     LshArgs lshArgs = LshArgs();
//     split_lsh_args(argc, argv, lshArgs);
//     Lsh *lsh = new Lsh(lshArgs);
//     lsh->print_lsh();

//     Metadata metadata = Metadata();
//     char **images = nullptr;

//     delete lsh;
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // For byte swapping
#include <arpa/inet.h>

struct MNISTHeader
{
    uint32_t magic_number;
    uint32_t num_images;
    uint32_t num_rows;
    uint32_t num_cols;
};

int main()
{
    std::ifstream file("./datasets/train-images.idx3-ubyte", std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        file.close();
        return 1;
    }

    MNISTHeader header;
    if (!file.read((char *)&header, sizeof(MNISTHeader)))
    {
        std::cerr << "Failed to read the header." << std::endl;
        file.close();
        return 1;
    }

    header.magic_number = ntohl(header.magic_number);

    header.num_images = ntohl(header.num_images);
    header.num_rows = ntohl(header.num_rows);
    header.num_cols = ntohl(header.num_cols);

    std::cout << "Magic Number: " << header.magic_number << std::endl;
    std::cout << "Number of Images: " << header.num_images << std::endl;
    std::cout << "Number of Rows: " << header.num_rows << std::endl;
    std::cout << "Number of Columns: " << header.num_cols << std::endl;

    // Read image data into a vector
    const int image_size = header.num_rows * header.num_cols;
    std::vector<char> image_data(image_size);
    if (!file.read(image_data.data(), image_size))
    {
        std::cerr << "Failed to read image data." << std::endl;
        file.close();
        return 1;
    }

    for (size_t i = 0; i < image_data.size(); i++)
    {
        std::cout << std::hex << (int)image_data.at(i) << ' ';
        if ((i + 1) % 16 == 0)
        {
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;

    file.close();

    return 0;
}
