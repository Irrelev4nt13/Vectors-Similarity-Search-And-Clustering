#pragma once

#include <iostream>

class Metadata
{
public:
    uint32_t magicNumber;
    uint32_t numOfImages;
    uint32_t numOfRows;
    uint32_t numOfColumns;
};

class Data
{
private:
    Metadata metadata;
    char **images;

public:
    Data(const Metadata &metadata, char **images);
    ~Data();
    void print();
};
