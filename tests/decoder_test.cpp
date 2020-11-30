//
// Created by igor on 30.11.2020.
//

#include "../decoder.h"

void performDecodeInstructionTest(uint32_t instr_code, InstrType type){
    Instruction instr = Instruction();
    instr.decode(instr_code);

    if (instr.type != type) {
        std::cout << type << " parsed incorrectly" << std::endl;
    }
}

int main()
{
    //LUI
    performDecodeInstructionTest(0b10101010101010101010111000010111, UType);
    //JAL
    performDecodeInstructionTest(0b10000000000100000000111001101111, JType);
    //ADD
    performDecodeInstructionTest(0b00000001101100100101000100110011, RType);
    //LB
    performDecodeInstructionTest(0b10000110001100011000111000000011, IType);
    //SB
    performDecodeInstructionTest(0b10101110001100001000001000100011, SType);
    //BEQ
    performDecodeInstructionTest(0b11010100001100100000101001100011, BType);

    return 0;
}

