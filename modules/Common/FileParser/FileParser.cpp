#include <vector>
#include <fstream>
#include <arpa/inet.h>

#include "Image.hpp"
#include "FileParser.hpp"

#ifdef DEBUG
#include <unistd.h>
#include <limits.h>
#include "Utils.hpp"
#endif

FileParser::FileParser(std::string inputFile)
{

#ifdef DEBUG
    inputFile = getFullPath(inputFile);
#endif

    std::ifstream file(inputFile, std::ios::binary);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        file.close();
        exit(EXIT_FAILURE);
    }

    if (!file.read((char *)&metadata, sizeof(Metadata)))
    {
        std::cerr << "Failed to read the header." << std::endl;
        file.close();
        exit(EXIT_FAILURE);
    }

    metadata.magicNumber = ntohl(metadata.magicNumber);
    metadata.numOfImages = ntohl(metadata.numOfImages);
    metadata.numOfRows = ntohl(metadata.numOfRows);
    metadata.numOfColumns = ntohl(metadata.numOfColumns);

    const int image_size = metadata.numOfRows * metadata.numOfColumns;

    images.resize(metadata.numOfImages);

    uint8_t byte;
    for (std::size_t i = 0; i < images.size(); i++)
    {
        images[i] = new Image;
        images[i]->pixels.resize(metadata.numOfRows * metadata.numOfColumns);
        images[i]->id = i;

        for (std::size_t j = 0; j < metadata.numOfRows * metadata.numOfColumns; ++j)
        {
            if (!file.read((char *)&byte, 1))
            {
                std::cerr << "Failed to read image data." << std::endl;
                file.close();
                exit(EXIT_FAILURE);
            }
            images[i]->pixels[j] = static_cast<double>(byte);
        }
    }

    file.close();
}

FileParser::~FileParser()
{
    for (const ImagePtr image_ptr : images)
        delete image_ptr;
}
