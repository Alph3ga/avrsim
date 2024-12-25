#include <transfer.hpp>

int Transfer::LDI(instruction inst, CPU& cpu){
    uint8_t K= inst[2] & 0xFF;
    cpu.set_reg(inst[1] & 0xFF, K);

    return 1;
}

int Transfer::MOV(instruction inst, CPU& cpu){
    cpu.set_reg(inst[1] & 0xFF, cpu.get_reg(inst[2] & 0xFF));

    return 1;
}

int Transfer::OUT(instruction inst, CPU& cpu){
    uint8_t P= inst[1] & 0xFF;
    uint8_t R= inst[2] & 0xFF;
    cpu.set_ioreg(P, cpu.get_reg(R));

    return 1;
}

int Transfer::IN(instruction inst, CPU& cpu){
    uint8_t P= inst[2] & 0xFF;
    uint8_t R= inst[1] & 0xFF;
    cpu.set_reg(R, cpu.get_ioreg(P));

    return 1;
}