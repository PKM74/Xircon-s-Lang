#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <optional>

enum class TokenType {
        // Basic Functions
    exit,
    print,
    ret,
    import,
    func,
        // Variables
    _int,
    _float,
    _char,
    _string,
    boolean,
        // Ifs and Loops
    _if,
    loop,
    _else,
    elif,
    _while,
        // Internal Stuff
    int_lit,
    float_lit,
    string_lit,
    char_lit,
    boolean_lit,
    semicolon
};

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};

class Tokenizer {
    public:
        inline explicit Tokenizer(const std::string& src) 
            :m_src(std::move(src))
        {
        }

        inline std::vector<Token> Tokenize() {
            std::vector<Token> Tokens;
            std::string buffer {};
            while(Peek().has_value()) {
                if (std::isalpha(Peek().value())) {
                    buffer.push_back(Consume());
                    while (Peek().has_value() && std::isalnum(Peek().value())) {
                        buffer.push_back(Consume());
                    }
                    if (buffer == "exit") {
                        Tokens.push_back({.type = TokenType::exit});
                        buffer.clear();
                        continue;
                    } else {
                        std::cerr << "Fuck... Something Went Wrong!" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                } else if (std::isdigit(Peek().value())) {
                    buffer.push_back(Consume());
                    while (Peek().has_value() && isdigit(Peek().value())) {
                        buffer.push_back(Consume());
                    }
                    Tokens.push_back({.type = TokenType::int_lit, .value = buffer});
                    buffer.clear();
                    continue;
                } else if (Peek().value() == ';') {
                    Consume();
                    Tokens.push_back({.type = TokenType::semicolon});
                    continue;
                } else if (Peek().value() == '!') { // Completely Ignores Coments
                    while (Peek().has_value() && Peek().value() != '\n') {
                        Consume();
                    }
                    continue;
                } else if (std::isspace(Peek().value())) {
                    Consume();
                    continue;
                } else {
                    std::cerr << "Fuck... Something Went Wrong!!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            m_index = 0; // Doubt i'll EVER need to have this... but i prolly should.. cuz.. edge cases...
            return Tokens;
        }



    private:

        [[nodiscard]] inline std::optional<char> Peek(int ahead = 1) const {
            if (m_index + ahead > m_src.length()) {
                return {};
            } else {
                return m_src.at(m_index);
            }
        }    

        inline char Consume() {
            return m_src.at(m_index++);

        }

        const std::string m_src;
        size_t m_index = 0;
};