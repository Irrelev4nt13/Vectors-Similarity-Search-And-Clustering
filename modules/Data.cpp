#include <Data.hpp>

Data::Data(const Metadata &metadata, char **images) : metadata(metadata), images(images)
{
}

Data::~Data()
{
}

void Data::print()
{
    std::cout << metadata.magicNumber << std::endl;
    std::cout << metadata.numOfImages << std::endl;
    std::cout << metadata.numOfRows << std::endl;
    std::cout << metadata.numOfColumns << std::endl;
}