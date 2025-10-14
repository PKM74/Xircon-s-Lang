#include <iostream>
#include <fstream>
#include <sstream>

#define version "RD-00002"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main(int argC, char *argV[]) {
    if(argC > 2) {
        std::cerr << "Usage: xic [OPTIONS] [INPUT FILE]\n" << std::endl;
        return EXIT_FAILURE;
    }

    std::fstream input(argV[1], std::ios::in);
    std::stringstream contents_stream;
    contents_stream << input.rdbuf();
    input.close();

    return 0;
}