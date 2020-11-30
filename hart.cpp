//
// Created by igor on 30.11.2020.
//

#include "hart.h"


Hart::Hart(uint32_t initial_pc, std::vector<uint32_t> &instructions)
{
    pc = initial_pc;
    for(unsigned int & reg : regs)
        reg = 0;
    memory.resize(instructions.size() * sizeof(uint32_t));
    memcpy(&memory[0], (void*)instructions.data(), instructions.size() * sizeof(uint32_t));
}

void Hart::SetPc(uint32_t pc_value)
{
    pc = pc_value;
}

void Hart::SetReg(uint8_t reg_num, uint32_t reg_value)
{
    checkRegisterNumber(reg_num);
    if(reg_num != 0)
        regs[reg_num] = reg_value;
}

void Hart::WriteWord(uint32_t addr, uint32_t data)
{
    checkOutOfMem(addr, memory.size() - 3);
    memory[addr + 3] = (uint8_t)data;
    memory[addr + 2] = (uint8_t)(data >> 8);
    memory[addr + 1] = (uint8_t)(data >> 16);
    memory[addr]  = (uint8_t)(data >> 24);
}

void Hart::WriteHalfWord(uint32_t addr, uint16_t data)
{
    checkOutOfMem(addr, memory.size() - 1);
    memory[addr + 1] = (uint8_t)data;
    memory[addr]  = (uint8_t)(data >> 8);
}

void Hart::WriteByte(uint32_t addr, uint8_t data)
{
    checkOutOfMem(addr, memory.size());
    memory[addr] = data;
}

void Hart::MemDump()
{
    std::ofstream fout("./mem_dump.txt", std::ios::out | std::ios::binary);
    fout.write((char*)&memory[0], memory.size() * sizeof(uint8_t));
    fout.close();
}

uint32_t Hart::GetPc()
{
    return pc;
}

uint32_t Hart::GetReg(uint8_t reg_num) {
    checkRegisterNumber(reg_num);
    return regs[reg_num];
}

uint32_t Hart::ReadWord(uint32_t addr)
{
    checkOutOfMem(addr, memory.size() - 3);
    return ((uint32_t) memory[addr] << 24) | ((uint32_t) memory[addr + 1] << 16) | ((uint32_t) memory[addr + 2] << 8) | (uint32_t) memory[addr];
}

uint16_t Hart::ReadHalfWord(uint32_t addr)
{
    checkOutOfMem(addr, memory.size() - 1);
    return ((uint16_t) memory[addr] << 8) | (uint16_t) memory[addr + 1];
}

uint8_t Hart::ReadByte(uint32_t addr)
{
    checkOutOfMem(addr, memory.size());
    return memory[addr];
}