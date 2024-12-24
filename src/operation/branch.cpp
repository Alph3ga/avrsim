#include <branch.hpp>

int Branch::JMP(instruction inst, CPU& cpu){
    uint16_t pos= inst[1] & 0xFFFF;
    cpu.PC= pos; 

    return 3;
}

int Branch::BRNE(instruction inst, CPU& cpu){
    uint16_t pos= inst[1] & 0xFFFF;
    if(cpu.get_ioreg_bit(Register::SREG, Register::status_bit::Z)){
        return 1;
    }
    else{
        cpu.PC= pos;
        return 2;
    }
}