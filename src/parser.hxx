#pragma once

#include <variant>
#include <vector>
#include <optional>
#include <iostream>

#include "tokenizer.hxx"

namespace node {
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
        if (Peek().has_value()) {
            if (Peek().value().type == TokenType::int_lit) {
                return node::Expression {.variant = node::ExpressionIntLit {.int_lit = Consume()}};
            } else if (Peek().value().type == TokenType::identifier) {
                return node::Expression {.variant = node::ExpressionIdentifier {.identifier = Consume()}};
            } else {
                std::cerr << "Invalid Expression: Type not Implemented!" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "Invalid Expression: No Value!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    std::optional<node::Statement> Parse_statement() {
        if (Peek().has_value()) {
            if(Peek().value().type == TokenType::exit) {
                if (auto expr = Parse_expression()) {
                    Consume();
                    if (Peek().has_value() && Peek().value().type == TokenType::semicolon) {
                        Consume();
                        return node::Statement {.variant = node::StatementExit {.expression = expr.value()}};
                    } else {
                        std::cerr << "Invalid Statement: Expected Semicolon" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    
                } else {
                    std::cerr << "Invalid Statement: No Exit Value!" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else if (Peek().value().type == TokenType::_int) {
                // TODO
                exit(11);
            } else {
                std::cerr << "Invalid Statement: Type not Implemented" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "Invalid Statement: No Value!" << std::endl;
            exit(EXIT_FAILURE);
        }

    }

    std::optional<node::Program> Parse_program() {
        node::Program prog;
        while (Peek().has_value()) {
            if (auto stmt = Parse_statement()) {
                prog.statements.push_back(stmt.value());
            } else {
                std::cerr << "Statement Parser Undefined Error!" << std::endl;
                exit(EXIT_FAILURE);
            }
        } if (!Peek().has_value()) {
            return {};
        }
        return prog;
    }

    private:
        [[nodiscard]] inline std::optional<Token> Peek(int offset = 0) const {
        if (m_index + offset >= m_Tokens.size()) {
            return {};
        } else {
            return m_Tokens[m_index + offset];
        }
    }

    inline Token Consume() {
        return m_Tokens[m_index++];
    }
    const std::vector<Token> m_Tokens;
    size_t m_index = 0;
};