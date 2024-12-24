#pragma once
#include <cpu.hpp>
#include <defs.hpp>
#include <vector>

typedef std::vector<uint32_t>& instruction;

namespace Transfer{
    int MOV(instruction, CPU&);
    int LDI(instruction, CPU&);
}