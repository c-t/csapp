#ifndef MINIOBJDUMP_H
#define MINIOBJDUMP_H

#include <elf.h>

int read_elf_header(const char *filename, Elf64_Ehdr *header);
void print_elf_header(const Elf64_Ehdr *header);
void print_sections(const char *filename, const Elf64_Ehdr *header);
void print_hex_dump(const char *filename, const Elf64_Ehdr *header, const char *section_name);

#endif
