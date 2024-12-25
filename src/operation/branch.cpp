#include <branch.hpp>

int Branch::JMP(instruction inst, CPU& cpu){
    uint16_t pos= inst[1] & 0xFFFF;
    cpu.PC= pos; 

    return 3;
}

int Branch::CALL(instruction inst, CPU& cpu){
    uint16_t pos= inst[1] & 0xFFFF;

    uint16_t SP= cpu.get_SP();
    uint16_t ret_PC= cpu.PC;  // Not considering 2 word inst
    cpu.set_data(SP--, ret_PC & 0xFF); 
    cpu.set_data(SP--, ret_PC>>8);
    cpu.set_SP(SP);
    
    cpu.PC= pos;

    return 4;
}

int Branch::RET(instruction inst, CPU& cpu){
    uint16_t SP= cpu.get_SP();

    uint8_t PCH= cpu.get_data(++SP);
    uint8_t PCL= cpu.get_data(++SP);

    cpu.set_SP(SP);

    uint16_t ret_PC= 0;
    ret_PC|= PCL;
    ret_PC|= PCH<<8;

    cpu.PC= ret_PC;

    return 4;
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