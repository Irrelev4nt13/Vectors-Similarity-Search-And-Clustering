#ifndef FILEPARSER_HPP_
#define FILEPARSER_HPP_

#include <vector>

#include "Image.hpp"
#include "PublicTypes.hpp"

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
    std::vector<ImagePtr> images;

public:
    FileParser(std::string inputFile);
    ~FileParser();
    inline const Metadata &GetMetadata() const { return metadata; }
    inline const std::vector<ImagePtr> &GetImages() const { return images; }
    std::string getFullPath();
};

#endif