#pragma once
#include <stdint.h>

class CPU{
public:
    uint16_t SP;
    uint16_t PC;

    uint8_t data[2048];

    long long unsigned int ticks= 0;

    static constexpr uint8_t WORD_SIZE= 0xFF;
    static constexpr double TICK_TIME= 1.25e-7;

    static constexpr uint16_t RAMEND= 0x85F;
    static constexpr uint16_t REG_OFFSET= 0x00;
    static constexpr uint16_t IOREG_OFFSET= 0x20;
    static constexpr uint16_t SRAM_OFFSET= 0x60;

    CPU();

    bool next_tick(int inc= 1);

    inline unsigned int uptime_ms();
    inline unsigned int uptime_us(); 

    // Register address space 0x00-0x1F
    inline uint8_t get_reg(uint8_t addr){
        return get_data(addr+REG_OFFSET);
    }
    inline bool set_reg(uint8_t addr, uint8_t val){
        return set_data(addr+REG_OFFSET, val);
    }

    // IO address space 0x00-0x3F
    inline uint8_t get_ioreg(uint8_t addr){
        return get_data(addr+IOREG_OFFSET);
    }
    inline bool set_ioreg(uint8_t addr, uint8_t val){
        return set_data(addr+IOREG_OFFSET, val);
    }

    // Interal SRAM addresses 0x00-0x85
    inline uint8_t get_sram(uint8_t addr){
        return get_data(addr+SRAM_OFFSET);
    }
    inline bool set_sram(uint8_t addr, uint8_t val){
        return set_data(addr+SRAM_OFFSET, val);
    }

    // Data address space 0x00-0x85F (Registers 0x00-0x1F, IO Registers 0x20-0x5F, SRAM 0x60-0x85F)
    uint8_t get_data(uint8_t);
    bool set_data(uint8_t, uint8_t);

    // functions for 16 bit addressing, using the higher byte data address

    // Register address space 0x00-0x1F
    inline uint16_t wget_reg(uint8_t addr){
        return wget_data(addr+REG_OFFSET);
    }
    inline bool wset_reg(uint8_t addr, uint16_t val){
        return wset_data(addr+REG_OFFSET, val);
    }

    // IO address space 0x00-0x3F
    inline uint16_t wget_ioreg(uint8_t addr){
        return wget_data(addr+IOREG_OFFSET);
    }
    inline bool wset_ioreg(uint8_t addr, uint16_t val){
        return wset_data(addr+IOREG_OFFSET, val);
    }

    // Interal SRAM addresses 0x00-0x85
    inline uint16_t wget_sram(uint8_t addr){
        return wget_data(addr+SRAM_OFFSET);
    }
    inline bool wset_sram(uint8_t addr, uint16_t val){
        return wset_data(addr+SRAM_OFFSET, val);
    }

    // Data address space 0x00-0x85F (Registers 0x00-0x1F, IO Registers 0x20-0x5F, SRAM 0x60-0x85F)
    uint16_t wget_data(uint8_t);
    bool wset_data(uint8_t, uint16_t); 

    inline bool set_reg_bit(uint8_t addr, uint8_t bit){
        return set_data_bit(addr+REG_OFFSET, bit);
    }
    inline bool clear_reg_bit(uint8_t addr, uint8_t bit){
        return clear_data_bit(addr+REG_OFFSET, bit);
    }

    inline bool set_ioreg_bit(uint8_t addr, uint8_t bit){
        return set_data_bit(addr+IOREG_OFFSET, bit);
    }
    inline bool clear_ioreg_bit(uint8_t addr, uint8_t bit){
        return clear_data_bit(addr+IOREG_OFFSET, bit);
    }

    bool set_data_bit(uint8_t, uint8_t);
    bool clear_data_bit(uint8_t, uint8_t);

};