#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#define version "RD-00002"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

const char *output_filename = "out.asm";

enum class TokenType {
    ret,
    int_lit,
    semicolon,
    comment
};

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};

std::vector<Token> Tokenize(const std::string& str) {
    std::vector<Token> Tokens;

    std::string buffer {};
    for (int i = 0; i < str.length(); i++) {
        char c = str.at(i);
        if (std::isalpha(c)) {
            buffer.push_back(c);
            i++;
            while (std::isalnum(str.at(i))) {
                buffer.push_back(str.at(i));
                i++;
            }
            i--;

            if (buffer == "ret") { // return func checkor
                Tokens.push_back({.type = TokenType::ret});
                buffer.clear();
                continue;
            }
        } else if (std::isdigit(c)) {
            buffer.push_back(c);
            i++;
            while (std::isdigit(str.at(i))) {
                buffer.push_back(str.at(i));
                i++;
            }
            i--;
            Tokens.push_back({.type = TokenType::int_lit, .value = buffer});
            buffer.clear();
        }
        else if (c == ';') { // legit only checks for a semicolon
            Tokens.push_back({.type = TokenType::semicolon});
        }
        else if (std::isspace(c)) {
            continue;
        }
    }

    return Tokens;
}

std::string Tokens_To_Asm(const std::vector<Token>& Tokens) {
    std::stringstream output;
    output << "global _start\nstart:\n";
    for (int i = 0; i < Tokens.size(); i++) {
        const Token& Token = Tokens.at(i);
        if (Token.type == TokenType::ret) {
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

    std::vector<Token> Tokens = Tokenize(contents);

    {
        std::fstream file(output_filename, std::ios::out);
        file << Tokens_To_Asm(Tokens);
    }

    return EXIT_SUCCESS;
}