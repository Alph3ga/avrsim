#pragma once
#include <stdint.h>

constexpr uint16_t INST_SIZE= 131;
constexpr uint16_t NUM_PINS= 4;

#define _1_BYTE 0x8
#define _2_BYTE 0x10
#define _3_BYTE 0x18

constexpr uint8_t BIT7=128;
constexpr uint8_t BIT6=64;
constexpr uint8_t BIT5=32;
constexpr uint8_t BIT4=16;
constexpr uint8_t BIT3=8;
constexpr uint8_t BIT2=4;
constexpr uint8_t BIT1=2;
constexpr uint8_t BIT0=1;

static const char* INST[]={
// Arithmetic (0-27):
    "ADD",  // Rd, Rr Add two Registers Rd ← Rd + Rr Z,C,N,V,H 1
    "ADC",  // Rd, Rr Add with Carry two Registers Rd ← Rd + Rr + C Z,C,N,V,H 1
    "ADIW",  // Rdl,K Add Immediate to Word Rdh:Rdl ← Rdh:Rdl + K Z,C,N,V,S 2
    "SUB",  // Rd, Rr Subtract two Registers Rd ← Rd - Rr Z,C,N,V,H 1
    "SUBI",  // Rd, K Subtract Constant from Register Rd ← Rd - K Z,C,N,V,H 1
    "SBC",  // Rd, Rr Subtract with Carry two Registers Rd ← Rd - Rr - C Z,C,N,V,H 1
    "SBCI",  // Rd, K Subtract with Carry Constant from Reg. Rd ← Rd - K - C Z,C,N,V,H 1
    "SBIW",  // Rdl,K Subtract Immediate from Word Rdh:Rdl ← Rdh:Rdl - K Z,C,N,V,S 2
    "AND",  // Rd, Rr Logical AND Registers Rd ← Rd • Rr Z,N,V 1
    "ANDI",  // Rd, K Logical AND Register and Constant Rd ← Rd • K Z,N,V 1
    "OR",  // Rd, Rr Logical OR Registers Rd ← Rd v Rr Z,N,V 1
    "ORI",  // Rd, K Logical OR Register and Constant Rd ← Rd v K Z,N,V 1
    "EOR",  // Rd, Rr Exclusive OR Registers Rd ← Rd ⊕ Rr Z,N,V 1
    "COM",  // Rd One’s Complement Rd ← $FF − Rd Z,C,N,V 1
    "NEG",  // Rd Two’s Complement Rd ← $00 − Rd Z,C,N,V,H 1
    "SBR",  // Rd,K Set Bit(s) in Register Rd ← Rd v K Z,N,V 1
    "CBR",  // Rd,K Clear Bit(s) in Register Rd ← Rd • ($FF - K) Z,N,V 1
    "INC",  // Rd Increment Rd ← Rd + 1 Z,N,V 1
    "DEC",  // Rd Decrement Rd ← Rd − 1 Z,N,V 1
    "TST",  // Rd Test for Zero or Minus Rd ← Rd • Rd Z,N,V 1
    "CLR",  // Rd Clear Register Rd ← Rd ⊕ Rd Z,N,V 1
    "SER",  // Rd Set Register Rd ← $FF None 1
    "MUL",  // Rd, Rr Multiply Unsigned R1:R0 ← Rd x Rr Z,C 2
    "MULS",  // Rd, Rr Multiply Signed R1:R0 ← Rd x Rr Z,C 2
    "MULSU",  // Rd, Rr Multiply Signed with Unsigned R1:R0 ← Rd x Rr Z,C 2
    "FMUL",  // Rd, Rr Fractional Multiply Unsigned R1:R0 ← (Rd x Rr) << 1 Z,C 2
    "FMULS",  // Rd, Rr Fractional Multiply Signed R1:R0 ← (Rd x Rr) << 1 Z,C 2
    "FMULSU",  // Rd, Rr Fractional Multiply Signed with Unsigned R1:R0 ← (Rd x Rr) << 1 Z,C 2

// Branch (28-63):
    "RJMP",  // k Relative Jump PC ← PC + k + 1 None 2
    "IJMP",  // Indirect Jump to (Z) PC ← Z None 2
    "JMP",  // k Direct Jump PC ← k None 3
    "RCALL",  // k Relative Subroutine Call PC ← PC + k + 1 None 3
    "ICALL",  // Indirect Call to (Z) PC ← Z None 3
    "CALL",  // k Direct Subroutine Call PC ← k None 4
    "RET",  // Subroutine Return PC ← Stack None 4
    "RETI",  // Interrupt Return PC ← Stack I 4
    "CPSE",  // Rd,Rr Compare, Skip if Equal if (Rd = Rr) PC ← PC + 2 or 3 None 1 / 2 / 3
    "CP",  // Rd,Rr Compare Rd − Rr Z, N,V,C,H 1
    "CPC",  // Rd,Rr Compare with Carry Rd − Rr − C Z, N,V,C,H 1
    "CPI",  // Rd,K Compare Register with Immediate Rd − K Z, N,V,C,H 1
    "SBRC",  // Rr, b Skip if Bit in Register Cleared if (Rr(b)=0) PC ← PC + 2 or 3 None 1 / 2 / 3
    "SBRS",  // Rr, b Skip if Bit in Register is Set if (Rr(b)=1) PC ← PC + 2 or 3 None 1 / 2 / 3
    "SBIC",  // P, b Skip if Bit in I/O Register Cleared if (P(b)=0) PC ← PC + 2 or 3 None 1 / 2 / 3
    "SBIS",  // P, b Skip if Bit in I/O Register is Set if (P(b)=1) PC ← PC + 2 or 3 None 1 / 2 / 3
    "BRBS",  // s, k Branch if Status Flag Set if (SREG(s) = 1) then PC←PC+k + 1 None 1 / 2
    "BRBC",  // s, k Branch if Status Flag Cleared if (SREG(s) = 0) then PC←PC+k + 1 None 1 / 2
    "BREQ",  // k Branch if Equal if (Z = 1) then PC ← PC + k + 1 None 1 / 2
    "BRNE",  // k Branch if Not Equal if (Z = 0) then PC ← PC + k + 1 None 1 / 2
    "BRCS",  // k Branch if Carry Set if (C = 1) then PC ← PC + k + 1 None 1 / 2
    "BRCC",  // k Branch if Carry Cleared if (C = 0) then PC ← PC + k + 1 None 1 / 2
    "BRSH",  // k Branch if Same or Higher if (C = 0) then PC ← PC + k + 1 None 1 / 2
    "BRLO",  // k Branch if Lower if (C = 1) then PC ← PC + k + 1 None 1 / 2
    "BRMI",  // k Branch if Minus if (N = 1) then PC ← PC + k + 1 None 1 / 2
    "BRPL",  // k Branch if Plus if (N = 0) then PC ← PC + k + 1 None 1 / 2
    "BRGE",  // k Branch if Greater or Equal, Signed if (N ⊕ V= 0) then PC ← PC + k + 1 None 1 / 2
    "BRLT",  // k Branch if Less Than Zero, Signed if (N ⊕ V= 1) then PC ← PC + k + 1 None 1 / 2
    "BRHS",  // k Branch if Half Carry Flag Set if (H = 1) then PC ← PC + k + 1 None 1 / 2
    "BRHC",  // k Branch if Half Carry Flag Cleared if (H = 0) then PC ← PC + k + 1 None 1 / 2
    "BRTS",  // k Branch if T Flag Set if (T = 1) then PC ← PC + k + 1 None 1 / 2
    "BRTC",  // k Branch if T Flag Cleared if (T = 0) then PC ← PC + k + 1 None 1 / 2
    "BRVS",  // k Branch if Overflow Flag is Set if (V = 1) then PC ← PC + k + 1 None 1 / 2
    "BRVC",  // k Branch if Overflow Flag is Cleared if (V = 0) then PC ← PC + k + 1 None 1 / 2
    "BRIE",  // k Branch if Interrupt Enabled if ( I = 1) then PC ← PC + k + 1 None 1 / 2
    "BRID",  // k Branch if Interrupt Disabled if ( I = 0) then PC ← PC + k + 1 None 1 / 2

// Data transfer (64-98):
    "MOV", // Rd, Rr Move Between Registers Rd ← Rr None 1
    "MOVW", // Rd, Rr Copy Register Word Rd+1:Rd ← Rr+1:Rr None 1
    "LDI", // Rd, K Load Immediate Rd ← K None 1
    "LD", // Rd, X Load Indirect Rd ← (X) None 2
    "LDD", // Rd,Y+q Load Indirect with Displacement Rd ← (Y + q) None 2
    "LDS", // Rd, k Load Direct from SRAM Rd ← (k) None 2
    "ST", // X, Rr Store Indirect (X) ← Rr None 2
    "STD", // Z+q,Rr Store Indirect with Displacement (Z + q) ← Rr None 2
    "STS", // k, Rr Store Direct to SRAM (k) ← Rr None 2
    "LPM", // Load Program Memory R0 ← (Z) None 3
    "SPM", // Store Program Memory (Z) ← R1:R0 None -
    "IN", // Rd, P In Port Rd ← P None 1
    "OUT", // P, Rr Out Port P ← Rr None 1
    "PUSH", // Rr Push Register on Stack Stack ← Rr None 2
    "POP", // Rd Pop Register from Stack Rd ← Stack None 2

// Bit (99-126):
    "SBI",  // P,b Set Bit in I/O Register I/O(P,b) ← 1 None 2
    "CBI",  // P,b Clear Bit in I/O Register I/O(P,b) ← 0 None 2
    "LSL",  // Rd Logical Shift Left Rd(n+1) ← Rd(n), Rd(0) ← 0 Z,C,N,V 1
    "LSR",  // Rd Logical Shift Right Rd(n) ← Rd(n+1), Rd(7) ← 0 Z,C,N,V 1
    "ROL",  // Rd Rotate Left Through Carry Rd(0)←C,Rd(n+1)← Rd(n),C←Rd(7) Z,C,N,V 1
    "ROR",  // Rd Rotate Right Through Carry Rd(7)←C,Rd(n)← Rd(n+1),C←Rd(0) Z,C,N,V 1
    "ASR",  // Rd Arithmetic Shift Right Rd(n) ← Rd(n+1), n=0..6 Z,C,N,V 1
    "SWAP",  // Rd Swap Nibbles Rd(3..0)←Rd(7..4),Rd(7..4)←Rd(3..0) None 1
    "BSET",  // s Flag Set SREG(s) ← 1 SREG(s) 1
    "BCLR",  // s Flag Clear SREG(s) ← 0 SREG(s) 1
    "BST",  // Rr, b Bit Store from Register to T T ← Rr(b) T 1
    "BLD",  // Rd, b Bit load from T to Register Rd(b) ← T None 1
    "SEC",  // Set Carry C ← 1 C 1
    "CLC",  // Clear Carry C ← 0 C 1
    "SEN",  // Set Negative Flag N ← 1 N 1
    "CLN",  // Clear Negative Flag N ← 0 N 1
    "SEZ",  // Set Zero Flag Z ← 1 Z 1
    "CLZ",  // Clear Zero Flag Z ← 0 Z 1
    "SEI",  // Global Interrupt Enable I ← 1 I 1
    "CLI",  // Global Interrupt Disable I ← 0 I 1
    "SES",  // Set Signed Test Flag S ← 1 S 1
    "CLS",  // Clear Signed Test Flag S ← 0 S 1
    "SEV",  // Set Twos Complement Overflow. V ← 1 V 1
    "CLV",  // Clear Twos Complement Overflow V ← 0 V 1
    "SET",  // Set T in SREG T ← 1 T 1
    "CLT",  // Clear T in SREG T ← 0 T 1
    "SEH",  // Set Half Carry Flag in SREG H ← 1 H 1
    "CLH",  // Clear Half Carry Flag in SREG H ← 0 H 1

// Control (127-130):
    "NOP",  // No Operation None 1
    "SLEEP",  // Sleep (see specific descr. for Sleep function) None 1
    "WDR",  // Watchdog Reset (see specific descr. for WDR/timer) None 1
    "BREAK",  // Break For On-Chip Debug Only None N/A
};

namespace Operation{
    enum Inst{
        ADD,  // Rd, Rr Add two Registers Rd ← Rd +
        ADC,  // Rd, Rr Add with Carry two Registers Rd ← Rd + Rr 
        ADIW,  // Rdl,K Add Immediate to Word Rdh:Rdl ← Rdh:Rdl 
        SUB,  // Rd, Rr Subtract two Registers Rd ← Rd -
        SUBI,  // Rd, K Subtract Constant from Register Rd ← Rd 
        SBC,  // Rd, Rr Subtract with Carry two Registers Rd ← Rd - Rr 
        SBCI,  // Rd, K Subtract with Carry Constant from Reg. Rd ← Rd - K 
        SBIW,  // Rdl,K Subtract Immediate from Word Rdh:Rdl ← Rdh:Rdl 
        AND,  // Rd, Rr Logical AND Registers Rd ← 
        ANDI,  // Rd, K Logical AND Register and Constant Rd ←
        OR,  // Rd, Rr Logical OR Registers Rd ← 
        ORI,  // Rd, K Logical OR Register and Constant Rd ←
        EOR,  // Rd, Rr Exclusive OR Registers Rd ← 
        COM,  // Rd One’s Complement Rd ← $FF
        NEG,  // Rd Two’s Complement Rd ← $00 −
        SBR,  // Rd,K Set Bit(s) in Register Rd ←
        CBR,  // Rd,K Clear Bit(s) in Register Rd ← Rd • ($
        INC,  // Rd Increment Rd ←
        DEC,  // Rd Decrement Rd ←
        TST,  // Rd Test for Zero or Minus Rd ← 
        CLR,  // Rd Clear Register Rd ← 
        SER,  // Rd Set Register 
        MUL,  // Rd, Rr Multiply Unsigned R1:R0 
        MULS,  // Rd, Rr Multiply Signed R1:R0 
        MULSU,  // Rd, Rr Multiply Signed with Unsigned R1:R0 
        FMUL,  // Rd, Rr Fractional Multiply Unsigned R1:R0 ← (Rd x
        FMULS,  // Rd, Rr Fractional Multiply Signed R1:R0 ← (Rd x
        FMULSU,  // Rd, Rr Fractional Multiply Signed with Unsigned R1:R0 ← (Rd x

        RJMP,  // k Relative Jump PC ← PC
        IJMP,  // Indirect Jump to (Z
        JMP,  // k Direct Jum
        RCALL,  // k Relative Subroutine Call PC ← PC
        ICALL,  // Indirect Call to (Z
        CALL,  // k Direct Subroutine Cal
        RET,  // Subroutine Return PC
        RETI,  // Interrupt Return
        CPSE,  // Rd,Rr Compare, Skip if Equal if (Rd = Rr) PC ← PC + 2 or 3
        CP,  // Rd,Rr Compare Rd − 
        CPC,  // Rd,Rr Compare with Carry Rd − Rr −
        CPI,  // Rd,K Compare Register with Immediate Rd −
        SBRC,  // Rr, b Skip if Bit in Register Cleared if (Rr(b)=0) PC ← PC + 2 or 3
        SBRS,  // Rr, b Skip if Bit in Register is Set if (Rr(b)=1) PC ← PC + 2 or 3
        SBIC,  // P, b Skip if Bit in I/O Register Cleared if (P(b)=0) PC ← PC + 2 or 3
        SBIS,  // P, b Skip if Bit in I/O Register is Set if (P(b)=1) PC ← PC + 2 or 3
        BRBS,  // s, k Branch if Status Flag Set if (SREG(s) = 1) then PC←PC+k
        BRBC,  // s, k Branch if Status Flag Cleared if (SREG(s) = 0) then PC←PC+k
        BREQ,  // k Branch if Equal if (Z = 1) then PC ← PC + k
        BRNE,  // k Branch if Not Equal if (Z = 0) then PC ← PC + k
        BRCS,  // k Branch if Carry Set if (C = 1) then PC ← PC + k
        BRCC,  // k Branch if Carry Cleared if (C = 0) then PC ← PC + k
        BRSH,  // k Branch if Same or Higher if (C = 0) then PC ← PC + k
        BRLO,  // k Branch if Lower if (C = 1) then PC ← PC + k
        BRMI,  // k Branch if Minus if (N = 1) then PC ← PC + k
        BRPL,  // k Branch if Plus if (N = 0) then PC ← PC + k
        BRGE,  // k Branch if Greater or Equal, Signed if (N ⊕ V= 0) then PC ← PC + k
        BRLT,  // k Branch if Less Than Zero, Signed if (N ⊕ V= 1) then PC ← PC + k
        BRHS,  // k Branch if Half Carry Flag Set if (H = 1) then PC ← PC + k
        BRHC,  // k Branch if Half Carry Flag Cleared if (H = 0) then PC ← PC + k
        BRTS,  // k Branch if T Flag Set if (T = 1) then PC ← PC + k
        BRTC,  // k Branch if T Flag Cleared if (T = 0) then PC ← PC + k
        BRVS,  // k Branch if Overflow Flag is Set if (V = 1) then PC ← PC + k
        BRVC,  // k Branch if Overflow Flag is Cleared if (V = 0) then PC ← PC + k
        BRIE,  // k Branch if Interrupt Enabled if ( I = 1) then PC ← PC + k
        BRID,  // k Branch if Interrupt Disabled if ( I = 0) then PC ← PC + k

        MOV, // Rd, Rr Move Between Registers
        MOVW, // Rd, Rr Copy Register Word Rd+1:Rd ←
        LDI, // Rd, K Load Immediat
        LD, // Rd, X Load Indirect 
        LDD, // Rd,Y+q Load Indirect with Displacement Rd ←
        LDS, // Rd, k Load Direct from SRAM 
        ST, // X, Rr Store Indirect 
        STD, // Y+q,Rr Store Indirect with Displacement (Y +
        STS, // k, Rr Store Direct to SRAM 
        LPM, // Load Program Memory 
        SPM, // Store Program Memory (Z)
        IN, // Rd, P In Por
        OUT, // P, Rr Out Por
        PUSH, // Rr Push Register on Stack St
        POP, // Rd Pop Register from Stack Rd

        SBI,  // P,b Set Bit in I/O Register I/O(
        CBI,  // P,b Clear Bit in I/O Register I/O(
        LSL,  // Rd Logical Shift Left Rd(n+1) ← Rd(n), Rd(0
        LSR,  // Rd Logical Shift Right Rd(n) ← Rd(n+1), Rd(7
        ROL,  // Rd Rotate Left Through Carry Rd(0)←C,Rd(n+1)← Rd(n),C←
        ROR,  // Rd Rotate Right Through Carry Rd(7)←C,Rd(n)← Rd(n+1),C←
        ASR,  // Rd Arithmetic Shift Right Rd(n) ← Rd(n+1), n
        SWAP,  // Rd Swap Nibbles Rd(3..0)←Rd(7..4),Rd(7..4)←
        BSET,  // s Flag Set SREG(s
        BCLR,  // s Flag Clear SREG(s
        BST,  // Rr, b Bit Store from Register to 
        BLD,  // Rd, b Bit load from T to Register R
        SEC,  // Set 
        CLC,  // Clear 
        SEN,  // Set Negative
        CLN,  // Clear Negative
        SEZ,  // Set Zero
        CLZ,  // Clear Zero
        SEI,  // Global Interrupt E
        CLI,  // Global Interrupt Di
        SES,  // Set Signed Test
        CLS,  // Clear Signed Test
        SEV,  // Set Twos Complement Over
        CLV,  // Clear Twos Complement Ove
        SET,  // Set T in
        CLT,  // Clear T in
        SEH,  // Set Half Carry Flag in
        CLH,  // Clear Half Carry Flag in

        NOP,  // No O
        SLEEP,  // Sleep (see specific descr. for Sleep f
        WDR,  // Watchdog Reset (see specific descr. for WD
        BREAK,  // Break For On-Chip Debu
    };
} 


static const char* IO_REG[]={
    "TWBR",
    "TWSR",
    "TWAR",
    "TWDR",
    "ADCL",
    "ADCH",
    "ADCSRA",
    "ADMUX",
    "ACSR",
    "UBRRL",
    "UCSRB",
    "UCSRA",
    "UDR",
    "SPCR",
    "SPSR",
    "SPDR",
    "PIND",
    "DDRD",
    "PORTD",
    "PINC",
    "DDRC",
    "PORTC",
    "PINB",
    "DDRB",
    "PORTB",
    "PINA",
    "DDRA",
    "PORTA",
    "EECR",
    "EEDR",
    "EEARL",
    "EEARH",
    "UCSRC",
    "UBRRH",
    "WDTCR",
    "ASSR",
    "OCR2",
    "TCNT2",
    "TCCR2",
    "ICR1L",
    "ICR1H",
    "OCR1BL",
    "OCR1BH",
    "OCR1AL",
    "OCR1AH",
    "TCNT1L",
    "TCNT1H",
    "TCCR1B",
    "TCCR1A",
    "SFIOR",
    "OCDR",
    "OSCCAL",
    "TCNT0",
    "TCCR0",
    "MCUCSR",
    "MCUCR",
    "TWCR",
    "SPMCR",
    "TIFR",
    "TIMSK",
    "GIFR",
    "GICR",
    "OCR0",
    "SPL",
    "SPH",
    "SREG"
};

namespace Register{
    enum IO{
        TWBR,
        TWSR,
        TWAR,
        TWDR,
        ADCL,
        ADCH,
        ADCSRA,
        ADMUX,
        ACSR,
        UBRRL,
        UCSRB,
        UCSRA,
        UDR,
        SPCR,
        SPSR,
        SPDR,
        PIND,
        DDRD,
        PORTD,
        PINC,
        DDRC,
        PORTC,
        PINB,
        DDRB,
        PORTB,
        PINA,
        DDRA,
        PORTA,
        EECR,
        EEDR,
        EEARL,
        EEARH,
        UCSRC,
        UBRRH= UCSRC,
        WDTCR,
        ASSR,
        OCR2,
        TCNT2,
        TCCR2,
        ICR1L,
        ICR1H,
        OCR1BL,
        OCR1BH,
        OCR1AL,
        OCR1AH,
        TCNT1L,
        TCNT1H,
        TCCR1B,
        TCCR1A,
        SFIOR,
        OCDR,
        OSCCAL= OCDR,
        TCNT0,
        TCCR0,
        MCUCSR,
        MCUCR,
        TWCR,
        SPMCR,
        TIFR,
        TIMSK,
        GIFR,
        GICR,
        OCR0,
        SPL,
        SPH,
        SREG
    };

    enum status_bit{
        C, Z, N, V, S, H, T, I
    };
}