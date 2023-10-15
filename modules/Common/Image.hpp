#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <iostream>
#include <vector>

class Image
{
public:
    int id;
    std::vector<uint8_t> pixels;

    Image(int id, const std::vector<uint8_t> &pixels) : id(id), pixels(pixels) {}

    Image() {}

    ~Image() {}
};

#endif