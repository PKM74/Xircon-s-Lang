#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#include "./tokesizer.hxx"
#include "./parser.hxx"
#include "./generator.hxx"

#define version "RD-00004"


const char *output_filename = "out.asm";

int main(int argC, char *argV[]) {
    if(argC > 2) {
        std::cerr << "Usage: xic [OPTIONS] [INPUT FILE]\n" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argV[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }
    Tokenizer Tokenizer(std::move(contents));
    std::vector<Token> Tokens = Tokenizer.Tokenize();

    Parser Parser(std::move(Tokens));
    std::optional<node::Exit> tree = Parser.Parse();

    if (!tree.has_value()) {
        std::cerr << "No exit Statement Found." << std::endl;
        exit(EXIT_FAILURE);
    }

    Generator Generator(tree.value());

    {
        std::fstream file(output_filename, std::ios::out);
        file << Generator.Generate();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}