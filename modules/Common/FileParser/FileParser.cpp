#include <vector>
#include <fstream>
#include <arpa/inet.h>

#include "Image.hpp"
#include "FileParser.hpp"

#ifdef DEBUG
#include <unistd.h>
#include <limits.h>
#endif

FileParser::FileParser(std::string inputFile)
{

#ifdef DEBUG
    inputFile = getFullPath() + "/" + inputFile;
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
    for (int i = 0; i < images.size(); i++)
    {
        images[i].pixels.resize(metadata.numOfRows * metadata.numOfColumns);
        images[i].id = i;
        if (!file.read((char *)images[i].pixels.data(), image_size))
        {
            std::cerr << "Failed to read image data." << std::endl;
            file.close();
            exit(EXIT_FAILURE);
        }
    }

    file.close();
}

FileParser::~FileParser() {}

std::string FileParser::getFullPath()
{
#ifdef DEBUG

    std::string cwd;
    char buffer[PATH_MAX];
    if (getcwd(buffer, sizeof(buffer)) != nullptr)
    {
        cwd = buffer;
    }

    int numParents = 3;
    std::string fullPath = cwd;
    for (int i = 0; i < numParents; i++)
    {
        size_t pos = fullPath.rfind('/');
        if (pos != std::string::npos)
        {
            fullPath = fullPath.substr(0, pos);
        }
    }

    return fullPath;
#endif
    return "";
}