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
            while(Peak().has_value()) {
                if (std::isalpha(Peak().value())) {
                    buffer.push_back(Consume());
                    while (Peak().has_value() && std::isalnum(Peak().value())) {
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
                } else if (std::isdigit(Peak().value())) {
                    buffer.push_back(Consume());
                    while (Peak().has_value() && isdigit(Peak().value())) {
                        buffer.push_back(Consume());
                    }
                    Tokens.push_back({.type = TokenType::int_lit, .value = buffer});
                    buffer.clear();
                    continue;
                } else if (Peak().value() == ';') {
                    Consume();
                    Tokens.push_back({.type = TokenType::semicolon});
                    continue;
                } else if (Peak().value() == '!') { // Completely Ignores Coments
                    while (Peak().has_value() && Peak().value() != '\n') {
                        Consume();
                    }
                    continue;
                } else if (std::isspace(Peak().value())) {
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

        [[nodiscard]] inline std::optional<char> Peak(int ahead = 1) const {
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
        int m_index = 0;
};