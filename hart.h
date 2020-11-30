//
// Created by igor on 30.11.2020.
//

#ifndef RISC_V_SIMULATOR_HART_H
#define RISC_V_SIMULATOR_HART_H

#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <err.h>
#include <fstream>
#include <string.h>

class Hart {
private:
    uint32_t pc;
    uint32_t regs[32];
    std::vector<uint8_t> memory;

public:
    Hart(uint32_t initial_pc, std::vector<uint32_t> &instructions);
    void SetPc(uint32_t pc_value);
    void SetReg(uint8_t reg_num, uint32_t reg_value);
    void WriteWord(uint32_t addr, uint32_t data);
    void WriteHalfWord(uint32_t addr, uint16_t data);
    void WriteByte(uint32_t addr, uint8_t data);
    void MemDump();
    uint32_t GetPc();
    uint32_t GetReg(uint8_t reg_num);
    uint32_t ReadWord(uint32_t addr);
    uint16_t ReadHalfWord(uint32_t addr);
    uint8_t ReadByte(uint32_t addr);
    ~Hart() = default;
};

void checkOutOfMem(uint32_t addr, uint32_t condition) {
    if (addr > condition) {
        errx(EXIT_FAILURE, "Out of physical memory, addr - %#010x.", addr);
    }
}

void checkRegisterNumber(uint8_t reg_num) {
    if (reg_num > 32) {
        errx(EXIT_FAILURE, "Reg number is more than 32");
    }
}

#endif //RISC_V_SIMULATOR_HART_H
