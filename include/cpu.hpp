#include <stdint.h>

class CPU{
public:
    uint8_t REG[32];
    uint16_t SP;
    uint16_t PC;
    uint8_t SREG;

    CPU();

    bool next_tick();
};