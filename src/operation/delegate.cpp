#include <delegate.hpp>

int delegate(instruction inst, CPU& cpu){
    uint16_t operation= inst[0];

    switch(operation){
    case Operation::ADD:
        return Arithmetic::ADD(inst, cpu);
    case Operation::ADC:
        return Arithmetic::ADC(inst, cpu);
    case Operation::SUB:
        return Arithmetic::SUB(inst, cpu);
    case Operation::DEC:
        return Arithmetic::DEC(inst, cpu);

    
    case Operation::JMP:
        return Branch::JMP(inst, cpu);
    case Operation::BRNE:
        return Branch::BRNE(inst, cpu);
    case Operation::CALL:
        return Branch::CALL(inst, cpu);
    case Operation::RET:
        return Branch::RET(inst, cpu);

    
    case Operation::MOV:
        return Transfer::MOV(inst, cpu);
    case Operation::LDI:
        return Transfer::LDI(inst, cpu);
    case Operation::IN:
        return Transfer::IN(inst, cpu);
    case Operation::OUT:
        return Transfer::OUT(inst, cpu);
    
    default:
        return -1;
        break;
    }
}