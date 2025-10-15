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

    std::optional<node::Expr> Parse_expr() {
        if (Peek().has_value() && Peek().value().type == TokenType::int_lit) {
            return node::Expr{.int_lit = Consume()};
        } else {
            return {};
        }
    }

    std::optional<node::Exit> Parse() {
        std::optional<node::Exit> exit_node;
        while(Peek().has_value()) {
            if (Peek().value().type == TokenType::exit) {
                Consume();
                if (auto node_expr = Parse_expr()) {
                    exit_node = node::Exit { .expr = node_expr.value() };
                } else {
                    std::cerr << "Invalid expression: No Exit Value!" << std::endl;
                    exit(EXIT_FAILURE);
                } if (Peek().has_value() && Peek().value().type == TokenType::semicolon) {
                    Consume();
                } else {
                    std::cerr << "Invalid expression: Missing Semicolon!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        m_index = 0;
        return exit_node;
    }

    private:
    [[nodiscard]] inline std::optional<Token> Peek(int ahead = 1) const {
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