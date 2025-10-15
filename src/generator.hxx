#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <optional>
#include <sstream>

#include "parser.hxx"



class Generator {
public:
    inline Generator(node::Exit root)
        :m_root(std::move(root))
    {
    }

    [[nodiscard]] std::string Generate() const {
        std::stringstream output;
        output << "global _start\n_start:\n";
        output << "    mov rax, 60\n";
        output << "    mov rdi, " << m_root.expr.int_lit.value.value() << "\n";
        output << "    syscall";
        return output.str();
    }

private:
    const node::Exit m_root;
};