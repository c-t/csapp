#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miniobjdump.h"

void print_summary(const char *filename, const Elf64_Ehdr *header)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    Elf64_Shdr *sections = malloc(sizeof(Elf64_Shdr) * header->e_shnum);

    if (sections == NULL)
    {
        fclose(file);
        return;
    }

    fseek(file, header->e_shoff, SEEK_SET);
    fread(sections, sizeof(Elf64_Shdr), header->e_shnum, file);

    Elf64_Shdr *shstr = &sections[header->e_shstrndx];

    char *shstrings = malloc(shstr->sh_size);

    fseek(file, shstr->sh_offset, SEEK_SET);

    fread(shstrings, shstr->sh_size, 1, file);

    size_t code_size = 0;
    size_t data_size = 0;
    size_t debug_size = 0;

    size_t largest_size = 0;
    const char *largest_section = "";

    for (int i = 0; i < header->e_shnum; i++)
    {
        const char *name = shstrings +sections[i].sh_name;

        if (strcmp(name, ".text") == 0)
        {
            code_size += sections[i].sh_size;
        }

        if (strcmp(name, ".rodata") == 0 || strcmp(name, ".data") == 0 || strcmp(name, ".bss") == 0)
        {
            data_size += sections[i].sh_size;
        }

        if (strncmp(name, ".debug", 6) == 0)
        {
            debug_size += sections[i].sh_size;
        }

        if (sections[i].sh_size > largest_size)
        {
            largest_size = sections[i].sh_size;
            largest_section = name;
        }
    }

    size_t symbol_count = 0;
    size_t function_count = 0;

    for (int i = 0;i < header->e_shnum; i++)
    {
        if (sections[i].sh_type != SHT_SYMTAB)
        {
            continue;
        }

        size_t count =sections[i].sh_size /sizeof(Elf64_Sym);

        Elf64_Sym *symbols =malloc(sections[i].sh_size);
        fseek(file,sections[i].sh_offset,SEEK_SET);
        fread(symbols,sections[i].sh_size,1,file);

        symbol_count = count;

        for (size_t j = 0; j < count; j++)
        {
            if (ELF64_ST_TYPE(symbols[j].st_info) == STT_FUNC)
            {
                if (symbols[j].st_shndx == SHN_UNDEF)
                {
                    continue;
                }
                function_count++;
            }
        }

        free(symbols);
    }

    printf("\n");
    printf("ELF Summary\n");
    printf("------------------------------------\n\n");
    printf("Entry Point      : 0x%lx\n", header->e_entry);
    printf("Total Sections   : %u\n", header->e_shnum);
    printf("Total Symbols    : %lu\n", symbol_count);
    printf("Functions        : %lu\n", function_count);
    printf("\n");
    printf("Code Size        : %lu bytes\n", code_size);
    printf("Data Size        : %lu bytes\n", data_size);
    printf("Debug Size       : %lu bytes\n", debug_size);
    printf("\n");
    printf("Largest Section  : %s (%lu bytes)\n", largest_section, largest_size);
    printf("\n");

    free(shstrings);
    free(sections);

    fclose(file);
}
