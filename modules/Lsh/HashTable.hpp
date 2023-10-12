#pragma once

#include <Image.hpp>

template <typename T>
using Bucket = std::vector<T>;

class HashTable
{
private:
    std::vector<Bucket<Image>> table;

public:
    HashTable(/* args */) {}
    ~HashTable() {}
    void insert() {}
    // int64_t GetHashVal(const Image *) {}
};
