#pragma once
#include <cpu.hpp>
#include <defs.hpp>
#include <vector>

typedef std::vector<uint32_t>& instruction;

namespace Arithmetic{
    int ADD(instruction inst, CPU& cpu);
    int ADC(instruction inst, CPU& cpu);
    int SUB(instruction inst, CPU& cpu);
    int DEC(instruction inst, CPU& cpu);
}