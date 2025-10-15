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


std::string Tokens_To_Asm(const std::vector<Token>& Tokens) {
    std::stringstream output;
    output << "global _start\n_start:\n";
    for (int i = 0; i < Tokens.size(); i++) {
        const Token& Token = Tokens.at(i);
        if (Token.type == TokenType::exit) {
            if (i + 1 < Tokens.size() && Tokens.at(i+1).type == TokenType::int_lit) {
                if (i + 2 < Tokens.size() && Tokens.at(i+2).type == TokenType::semicolon) {
                    output << "    mov rax, 60\n";
                    output << "    mov rdi, " << Tokens.at(i+1).value.value() << "\n";
                    output << "    syscall";
                }
            }
        }
    }
    return output.str();
}

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

    {
        std::fstream file(output_filename, std::ios::out);
        file << Tokens_To_Asm(Tokens);
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}