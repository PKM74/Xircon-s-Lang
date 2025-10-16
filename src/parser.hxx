#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <variant>
#include <optional>

#include "tokesizer.hxx"

namespace node  {
        // Internal Stuff
    struct ExpressionIntLit {
        Token int_lit;
    };

    struct ExpressionIdentifier {
        Token identifier;
    };

    struct Expression {
        std::variant<node::ExpressionIntLit, node::ExpressionIdentifier> variant;
    };

        // Still kinda internal stuff i guess...?

    struct StatementExit {
        node::Expression expression;
    };

    struct StatementInt {
        Token identifier;
        node::Expression expression;
    };

    struct Statement {
        std::variant<node::StatementExit, node::StatementInt> variant;
    };

    // Nuts

    struct Program {
        std::vector<node::Statement> statements;
    };
}

class Parser {
    public:
    inline explicit Parser(std::vector<Token> Tokens) 
        : m_Tokens(std::move(Tokens)) 
    {
    }

    std::optional<node::Expression> Parse_expression() {
        if (Peek().has_value() && Peek().value().type == TokenType::int_lit) {
            return node::Expression {.variant = node::ExpressionIntLit {.int_lit = Consume()}};
        } else if (Peek().has_value() && Peek().value().type == TokenType::identifier) {
            return node::Expression {.variant = node::ExpressionIdentifier {.identifier = Consume()}};
        } else {
            return {};
        }
    }

    std::optional<node::Statement> Parse_statement() {
        if (Peek().value().type == TokenType::exit) {
            Consume();
            node::StatementExit stmt_exit;
            if (auto node_expr = Parse_expression()) {
                stmt_exit = {.expression = node_expr.value()};
            } else {
                std::cerr << "Invalid expression: No Exit Value!" << std::endl;
                exit(EXIT_FAILURE);
            } if (Peek().has_value() && Peek().value().type == TokenType::semicolon) {
                Consume();
            } else {
                std::cerr << "Expected a Semicolon!" << std::endl;
                exit(EXIT_FAILURE);
            }
            return node::Statement{.variant = stmt_exit};
        } else if (
            Peek().has_value() && Peek().value().type == TokenType::_int && 
            Peek(1).has_value() && Peek(1).value().type == TokenType::identifier && 
            Peek(2).has_value() && Peek(2).value().type == TokenType::equals) {
            Consume();
            auto stmt_int = node::StatementInt { .identifier = Consume()};
            Consume();
            if (auto expr = Parse_expression()) {
                stmt_int.expression = expr.value();
            } else {
                std::cerr << "Invalid Expression!" << std::endl;
                exit(EXIT_FAILURE);
            } if (Peek().has_value() && Peek().value().type == TokenType::semicolon) {
                Consume();
            } else {
                std::cerr << "Expected a Semicolon!" << std::endl;
                exit(EXIT_FAILURE);
            }
            return node::Statement { .variant = stmt_int};
        } else {
            return {};
        }
    }

    std::optional<node::Program> Parse_program() {
        node::Program prog;
        while (Peek().has_value()) {
            if (auto stmt = Parse_statement()) {
                prog.statements.push_back(stmt.value());
            } else {
                std::cerr << "Invalid Statement!" << std::endl;
                exit(EXIT_FAILURE);
            }
        } if (!Peek().has_value()) {
            return {};
        }
        return prog;
    }

    private:
    [[nodiscard]] inline std::optional<Token> Peek(int ahead = 0) const {
        if (m_index + ahead >= m_Tokens.size()) {
            return {};
        } else {
            return m_Tokens.at(m_index + ahead);
        }
    }    

    inline Token Consume() {
        return m_Tokens.at(m_index++);

    }
    const std::vector<Token> m_Tokens;
    size_t m_index = 0;
};