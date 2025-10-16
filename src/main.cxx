#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#include "./tokenizer.hxx"
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
    std::optional<node::Program> prog = Parser.Parse_program();

    if (!prog.has_value()) {
        std::cerr << "Invalid Program!" << std::endl;
        exit(EXIT_FAILURE);
    }

    Generator Generator(prog.value());

    {
        std::fstream file(output_filename, std::ios::out);
        file << Generator.Generate_program();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}