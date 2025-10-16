#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <optional>
#include <sstream>

#include "parser-new.hxx"



class Generator {
public:
    inline Generator(node::Program prog)
        :m_prog(std::move(prog))
    {
    }

    void Generate_expression(const node::Expression& expr) {
        struct ExpressionVisitor {
            Generator* gen;
            void operator()(const node::ExpressionIntLit& expr_int_lit) const {
                gen->m_output << "mov rax, " << expr_int_lit.int_lit.value.value() << "\n";
                gen->m_output << "push rax\n";

            }
            void operator()(const node::ExpressionIdentifier& expr_ident) {
                //TODO
            }
        };
        ExpressionVisitor visitor{.gen = this};
        std::visit(visitor, expr.variant);
    }

    void Generate_statement(const node::Statement& stmt) {
        struct StatementVisitor {
            Generator* gen;
            void operator()(const node::StatementExit& stmt_exit) const {
                gen->Generate_expression(stmt_exit.expression);
                gen->m_output << "    mov rax, 60\n"; 
                gen->m_output << "    pop rdi\n";
                gen->m_output << "    syscall";
            }
            void operator()(const node::StatementInt& stmt_int) {
                //TODO
            }
        };

        StatementVisitor visitor{.gen = this};
        std::visit(visitor, stmt.variant);
    }

    [[nodiscard]] std::string Generate_program() {
        std::stringstream output;
        m_output << "global _start\n_start:\n";

        for (const node::Statement& stmt : m_prog.statements) {
            Generate_statement(stmt);
        }

        // Always exit no matter what (default code is 0)
        m_output << "    mov rax, 60\n"; 
        m_output << "    mov rdi, 0\n";
        m_output << "    syscall";
        return output.str();
    }

private:
    const node::Program m_prog;
    std::stringstream m_output;
};