#include <stdio.h>
#include <elf.h>
#include <stdlib.h>

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

void print_sections(const char* filename, const Elf64_Ehdr *header)
{
	FILE *file = fopen(filename, "rb");

	if(file == NULL)
	{
		perror("fopen");
		return;
	}

	Elf64_Shdr *sections = malloc(header->e_shentsize * header->e_shnum);

	if(sections == NULL)
	{
		fclose(file);
		return;
	}

	fseek(file, header->e_shoff, SEEK_SET);
	fread(sections, header->e_shentsize, header->e_shnum, file);

	Elf64_Shdr shstr = sections[header->e_shstrndx];
	char *strings = malloc(shstr.sh_size);
	
	fseek(file, shstr.sh_offset, SEEK_SET);
	fread(strings, shstr.sh_size, 1, file);

	printf("\nSections\n");
	printf("-----------------------------\n\n");

	for(int i = 0; i < header->e_shnum; i++)
	{
		printf("[%02d] %s\n", i, strings + sections[i].sh_name);
	}

	printf("\n");

	free(strings);
	free(sections);

	fclose(file);
}
