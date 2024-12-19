#include <cpu.hpp>

CPU::CPU(){
    PC= 0;
}

bool CPU::next_tick(){
    return ++PC;
}