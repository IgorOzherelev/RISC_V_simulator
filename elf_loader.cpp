//
// Created by igor on 30.11.2020.
//

#include "elf_loader.h"

void ElfLoader::load(std::vector<uint32_t> &instrs) {
    uint32_t mem_end;
    if(phdrnum > 0) {
        mem_end = phdrs[0].p_vaddr + phdrs[0].p_memsz;
    }
    for(int i = 0; i < phdrnum; i++) {
        if((phdrs[i].p_vaddr + phdrs[i].p_memsz) > mem_end) {
            mem_end = phdrs[i].p_vaddr + phdrs[i].p_memsz;
        }
    }

    instrs.resize(mem_end / sizeof(uint32_t));

    for(int i = 0; i < phdrnum; i++)
    {
        std::vector<uint32_t> buf(phdrs[i].p_memsz);
        lseek(fd, phdrs[i].p_offset, SEEK_SET);
        if(read(fd, &(buf[0]), phdrs[i].p_filesz) < 0)
            errx(EXIT_FAILURE, "read() failed : %s." , elf_errmsg(-1));
        instrs.insert(instrs.begin() + phdrs[i].p_vaddr / sizeof(uint32_t),
                            buf.begin(), buf.end());
    }

}

unsigned long int ElfLoader::entry() {
    return elfEhdr.e_entry;
}

void ElfLoader::init(const char *file_name) {
    if(elf_version(EV_CURRENT) == EV_NONE)
        errx(EXIT_FAILURE, "ELF library initialization failed: %s", elf_errmsg(-1));

    if((fd = open(file_name, O_RDONLY, 0)) < 0)
        err(EXIT_FAILURE, "open \" %s \" failed", file_name);

    if((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
        errx(EXIT_FAILURE, "elf_begin failed: %s.", elf_errmsg(-1));

    if(elf_kind(e) != ELF_K_ELF)
        errx(EXIT_FAILURE, "\" %s \" is not an ELF object.", file_name);

    if(gelf_getehdr(e , &elfEhdr) == NULL)
        errx(EXIT_FAILURE, "getehdr failed: %s.", elf_errmsg(-1));

    if(elfEhdr.e_machine != EM_RISCV)
        errx(EXIT_FAILURE, "\" %s \" is not a RISCV machine.", file_name);

    if(elfEhdr.e_ident[EI_CLASS] != ELFCLASS32)
        errx(EXIT_FAILURE, "\" %s \" is not a 32 bit machine.", file_name);

    if(elf_getphdrnum(e, &phdrnum) != 0)
        errx(EXIT_FAILURE, "elf_getphdrnum failed: %s." , elf_errmsg(-1));

    GElf_Phdr phdr;
    for(int i = 0; i < phdrnum; i++)
    {
        if(gelf_getphdr(e, i, &phdr) != &phdr)
            errx(EXIT_FAILURE, "getphdr failed: %s.", elf_errmsg(-1));
        phdrs.push_back(phdr);
    }
}
