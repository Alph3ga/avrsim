#include <cpu.hpp>

CPU::CPU(){
    PC= 0;
    ticks= 0;
}

uint8_t CPU::get_data(uint8_t addr){
    if(addr> RAMEND){
        return 0x00; // Do something
    }
    return this->data[addr];
}

bool CPU::set_data(uint8_t addr, uint8_t val){
    if(addr> RAMEND){
        return false; // Do something
    }

    this->data[addr]= val;

    return true;
}

uint16_t CPU::wget_data(uint8_t addr){
    uint8_t high, low;
    low= get_data(addr+1);
    high= get_data(addr);

    uint16_t res= 0;
    res|= low;
    res|= high<<8;

    return res;
}

bool CPU::wset_data(uint8_t addr, uint16_t val){
    return set_data(addr+1, (uint8_t)val) && set_data(addr, (uint8_t)(val>>8));
}

bool CPU::next_tick(int inc){
    return (this->ticks= this->ticks+inc);
}

inline unsigned int CPU::uptime_ms(){
    return this->ticks*TICK_TIME*1e3;
}
inline unsigned int CPU::uptime_us(){
    return this->ticks*TICK_TIME*1e6;
} 

bool CPU::set_data_bit(uint8_t addr, uint8_t bit){
    uint8_t data= this->get_data(addr);
    data|= 1<<bit;
    this->set_data(addr, data);
    return true;
}

bool CPU::clear_data_bit(uint8_t addr, uint8_t bit){
    uint8_t data= this->get_data(addr);
    data&= ~(1<<bit);
    this->set_data(addr, data);
    return true;
}

bool CPU::get_data_bit(uint8_t addr, uint8_t bit){
    uint8_t data= this->get_data(addr);
    data&= 1<<bit;
    return data;
}