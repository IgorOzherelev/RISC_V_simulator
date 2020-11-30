//
// Created by igor on 30.11.2020.
//

#ifndef RISC_V_SIMULATOR_DECODER_H
#define RISC_V_SIMULATOR_DECODER_H

#include <vector>
#include <iostream>

// Only RISCV32I base commands set is realized
enum InstrType {
    Unknown,
    RType,
    IType,
    SType,
    BType,
    UType,
    JType
};

class Instruction {
public:
    uint8_t oppcode;
    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
    uint32_t imm;
    InstrType type;

    Instruction()
    {
        oppcode = 0;
        rd = 0;
        funct3 = 0;
        rs1 = 0;
        rs2 = 0;
        funct7 = 0;
        imm = 0;
        type = Unknown;
    }
    void decode(uint32_t raw_instr);
    ~Instruction();
};

#endif //RISC_V_SIMULATOR_DECODER_H
