#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <optional>

#include "parser.hxx"



class Generator {
public:
    inline Generator(node::Exit root)
        :m_root(std::move(root))
    {
    }

    std::string Generate() {
        
    }

private:
    const node::Exit m_root;
};