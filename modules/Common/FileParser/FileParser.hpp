#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <arpa/inet.h>
#include <PublicTypes.hpp>

class Metadata
{
public:
    uint32_t magicNumber;
    uint32_t numOfImages;
    uint32_t numOfRows;
    uint32_t numOfColumns;
};

class FileParser
{
private:
    Metadata metadata;
    std::vector<Image> images;

public:
    FileParser(std::string inputFile)
    {
        std::ifstream file(inputFile, std::ios::binary);

        if (!file.is_open())
        {
            std::cerr << "Failed to open the file." << std::endl;
            file.close();
            exit(1);
        }

        if (!file.read((char *)&metadata, sizeof(Metadata)))
        {
            std::cerr << "Failed to read the header." << std::endl;
            file.close();
            exit(1);
        }

        metadata.magicNumber = ntohl(metadata.magicNumber);
        metadata.numOfImages = ntohl(metadata.numOfImages);
        metadata.numOfRows = ntohl(metadata.numOfRows);
        metadata.numOfColumns = ntohl(metadata.numOfColumns);

        const int image_size = metadata.numOfRows * metadata.numOfColumns;

        images.resize(metadata.numOfImages);
        for (int i = 0; i < images.size(); i++)
        {
            images[i].resize(metadata.numOfRows * metadata.numOfColumns);
            if (!file.read((char *)images[i].data(), image_size))
            {
                std::cerr << "Failed to read image data." << std::endl;
                file.close();
                exit(1);
            }
        }

        file.close();
    }

    ~FileParser() {}

    inline const Metadata &GetMetadata() const
    {
        return metadata;
    }

    inline const std::vector<Image> &GetImages() const
    {
        return images;
    }
};
