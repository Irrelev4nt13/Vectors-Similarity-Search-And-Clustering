#pragma once

#include <iostream>

class Metadata
{
public:
    int magicNumber;
    int numOfImages;
    int numOfRows;
    int numOfColumns;
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
