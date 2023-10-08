#include <iostream>
#include <Demo.hpp>

int main(int argc, char const *argv[])
{
    std::cout << "hello from lsh" << std::endl;

    Demo *demo = new Demo(1);
    std::cout << "hello from " << demo->dummyMethod() << std::endl;
    delete demo;

    return 0;
}
