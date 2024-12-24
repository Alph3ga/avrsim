#pragma once
#include <cpu.hpp>
#include <defs.hpp>
#include <vector>

typedef std::vector<uint32_t>& instruction;

namespace Branch{
    int JMP(instruction, CPU&);
    int BRNE(instruction, CPU&);
}