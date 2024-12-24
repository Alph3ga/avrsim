#include <arithmetic.hpp>

int Arithmetic::ADD(instruction inst, CPU& cpu){
    uint8_t A= cpu.get_reg(inst[1] & 0xFF);
    uint8_t B= cpu.get_reg(inst[2] & 0xFF);
    uint8_t res= A+B;

    cpu.set_reg(inst[1] & 0xFF, res);

    // Check carry
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::C, (A&BIT7)&&(B&BIT7) || (A&BIT7)&&(!res&BIT7) || (B&BIT7)&&(!res&BIT7));

    // Check zero
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::Z, res==0);

    // Check sign bit
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::N, res&BIT7);

    // Check overflow
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::V, (A&BIT7)&&(B&BIT7)&&(!res&BIT7) || (!A&BIT7)&&(!B&BIT7)&&(res&BIT7));

    // check sign
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::S, cpu.get_ioreg_bit(Register::SREG, Register::status_bit::N)^cpu.get_ioreg_bit(Register::SREG, Register::status_bit::V));

    // Check half carry
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::H, (A&BIT7)&&(B&BIT7) || (A&BIT7)&&(!res&BIT7) || (B&BIT7)&&(!res&BIT7));

    return 1;
}

int Arithmetic::ADC(instruction inst, CPU& cpu){
    uint8_t A= cpu.get_reg(inst[1] & 0xFF);
    uint8_t B= cpu.get_reg(inst[2] & 0xFF);
    uint8_t res= A+B+ cpu.get_ioreg_bit(Register::SREG, Register::status_bit::C);

    cpu.set_reg(inst[1] & 0xFF, res);

    // Check carry
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::C, (A&BIT7)&&(B&BIT7) || (A&BIT7)&&(!res&BIT7) || (B&BIT7)&&(!res&BIT7));

    // Check zero
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::Z, res==0);

    // Check sign bit
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::N, res&BIT7);

    // Check overflow
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::V, (A&BIT7)&&(B&BIT7)&&(!res&BIT7) || (!A&BIT7)&&(!B&BIT7)&&(res&BIT7));

    // check sign
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::S, cpu.get_ioreg_bit(Register::SREG, Register::status_bit::N)^cpu.get_ioreg_bit(Register::SREG, Register::status_bit::V));

    // Check half carry
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::H, (A&BIT7)&&(B&BIT7) || (A&BIT7)&&(!res&BIT7) || (B&BIT7)&&(!res&BIT7));

    return 1;
}

int Arithmetic::SUB(instruction inst, CPU& cpu){
    uint8_t A= cpu.get_reg(inst[1] & 0xFF);
    uint8_t B= cpu.get_reg(inst[2] & 0xFF);
    uint8_t res= A-B;

    cpu.set_reg(inst[1] & 0xFF, res);

    // Check carry
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::C, B>A);

    // Check zero
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::Z, res==0);

    // Check sign bit
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::N, res&BIT7);

    // Check overflow
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::V, (A&BIT7)&&(!B&BIT7)&&(!res&BIT7) || (!A&BIT7)&&(B&BIT7)&&(res&BIT7));

    // check sign
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::S, cpu.get_ioreg_bit(Register::SREG, Register::status_bit::N)^cpu.get_ioreg_bit(Register::SREG, Register::status_bit::V));

    // Check half carry
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::H, (!A&BIT7)&&(B&BIT7) || (B&BIT7)&&(res&BIT7) || (!A&BIT7)&&(res&BIT7));

    return 1;
}

int Arithmetic::DEC(instruction inst, CPU& cpu){
    uint8_t A= cpu.get_reg(inst[1] & 0xFF);
    uint8_t res= A-1;

    cpu.set_reg(inst[1] & 0xFF, res);

    // Check zero
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::Z, res==0);

    // Check sign bit
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::N, res&BIT7);

    // Check overflow
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::V, A==0x80);

    // check sign
    cpu.modify_ioreg_bit(Register::SREG, Register::status_bit::S, cpu.get_ioreg_bit(Register::SREG, Register::status_bit::N)^cpu.get_ioreg_bit(Register::SREG, Register::status_bit::V));

    return 1;
}