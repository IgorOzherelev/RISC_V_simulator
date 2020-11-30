//
// Created by igor on 30.11.2020.
//

#ifndef RISC_V_SIMULATOR_ELF_LOADER_H
#define RISC_V_SIMULATOR_ELF_LOADER_H

#include <iostream>
#include <iomanip>
#include <err.h>
#include <fcntl.h>
#include <gelf.h>
#include <unistd.h>
#include <vector>


class ElfLoader {
private:
    int fd;
    Elf *e;
    GElf_Ehdr elfEhdr;
    size_t  phdrnum;
    std::vector<GElf_Phdr> phdrs;

public:
    ElfLoader() {
        fd = 0;
        e = nullptr;
        phdrnum = 0;
    }

    void init(const char *file_name);
    unsigned long int entry();
    void load(std::vector<uint32_t> &instrs);
    ~ElfLoader() {
        elf_end(e);
        close(fd);
    }
};


#endif //RISC_V_SIMULATOR_ELF_LOADER_H
