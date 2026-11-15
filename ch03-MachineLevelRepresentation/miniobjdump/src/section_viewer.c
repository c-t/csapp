#include <stdio.h>

#include "miniobjdump.h"

static const char *elf_class(unsigned char value)
{
	switch(value)
	{
		case ELFCLASS64:
			return "ELF64";
		case ELFCLASS32:
			return "EFL32";
		default:
			return "Unknown";
	}
}

static const char *endianness(unsigned char value)
{
	switch(value)
	{
		case ELFDATA2LSB:
			return "Little Endian";
		case ELFDATA2MSB:
			return "Big Endian";
		default:
			return "Unknown";
	}
}

static const char *file_type(Elf64_Half type)
{
	switch(type)
	{
		case ET_EXEC:
			return "EXEC";
		case ET_DYN:
			return "DYN";
		case ET_REL:
			return "REL";
		default:
			return "Unknown";
	}
}

void print_elf_header(const Elf64_Ehdr *header)
{
	printf("\nELF Header\n");
	printf("-----------------------------\n");
	printf("Format		: %s\n", elf_class(header->e_ident[EI_CLASS]));
	printf("Endianness	: %s\n", endianness(header->e_ident[EI_DATA]));
	printf("Type		: %s\n", file_type(header->e_type));
	printf("Machine		: x86-64\n");
	printf("Entry Point	: 0x%lx\n", header->e_entry);
	printf("\n");
	printf("Program headers	: %u\n", header->e_phnum);
	printf("Sections headers: %u\n", header->e_shnum);
	printf("\n");
}
