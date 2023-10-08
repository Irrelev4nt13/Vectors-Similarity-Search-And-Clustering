#include <iostream>
#include <Demo.hpp>

Demo::Demo(int x) : x(x) {}

Demo::~Demo()
{
    std::cout << "destructor demo" << std::endl;
}

std::string Demo::dummyMethod()
{
    return "dummy method";
}