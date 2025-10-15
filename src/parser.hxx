#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <optional>

#include "tokesizer.hxx"

namespace node  {
    
    struct Expr {
        Token int_lit;
    };
    struct Exit {
        Expr expr;
    };
}

class Parser {
    public:
    inline explicit Parser(std::vector<Token> Tokens):
        m_Tokens(std::move(Tokens)) 
    {
    }

    std::optional<node::Expr> parse_expr() {
        if (Peak().has_value() && Peak().value().type == TokenType::int_lit) {
            return node::Expr{.int_lit = Consume()};
        } else {
            return {};
        }
    }

    std::optional<node::Exit> parse() {
        std::optional<node::Exit> exit_node;
        while(Peak().has_value()) {
            if (Peak().value().type == TokenType::exit) {
                Consume();
                if (auto node_expr = parse_expr()) {
                    exit_node = node::Exit { .expr = node_expr.value() };
                } else {
                    std::cerr << "Invalid expression: No Exit Value!" << std::endl;
                    exit(EXIT_FAILURE);
                } if (!Peak().has_value() || Peak().value().type != TokenType::semicolon) {
                    std::cerr << "Invalid expression: Missing Semicolon!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        m_index = 0;
        return exit_node;
    }

    private:
    [[nodiscard]] inline std::optional<Token> Peak(int ahead = 1) const {
        if (m_index + ahead > m_Tokens.size()) {
            return {};
        } else {
            return m_Tokens.at(m_index);
        }
    }    

    inline Token Consume() {
        return m_Tokens.at(m_index++);

    }
    const std::vector<Token> m_Tokens;
    size_t m_index = 0;
};