#ifndef BRUTEFORCE_HPP_
#define BRUTEFORCE_HPP_

#include <vector>

#include "Image.hpp"

std::vector<std::tuple<Image *, double>> BruteForce(const std::vector<Image *> &images_input, const Image &query, int k);

#endif