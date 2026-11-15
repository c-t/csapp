#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miniobjdump.h"

void print_disassembly(const char* filename, const Elf64_Ehdr *header)
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

	Elf64_Shdr *symtab = NULL;
	Elf64_Shdr *strtab = NULL;
	Elf64_Shdr *text = NULL;

	for(int i = 0; i < header->e_shnum; i++)
	{
		if(sections[i].sh_type == SHT_SYMTAB)
		{
			symtab = &sections[i];
			strtab = &sections[sections[i].sh_link];
			break;
		}

		if(sections[i].sh_type == SHT_PROGBITS)
		{
			//locate .text later
		}
	}
	
	//locate .shstrtab
	Elf64_Shdr *shstr = &sections[header->e_shstrndx];

	char *shstrings = malloc(shstr->sh_size);
	
	fseek(file, shstr->sh_offset, SEEK_SET);
	fread(shstrings, shstr->sh_size, 1, file);

	//Find .text
	for(int i = 0; i < header->e_shnum; i++)
	{
		const char *name = shstrings + sections[i].sh_name;
		if(strcmp(name, ".text") == 0)
		{
			text = &sections[i];
			break;
		}
	}

	if(symtab == NULL || strtab == NULL || text == NULL)
	{
		goto cleanup;
	}

	//Read .strtab
	char *strings = malloc(strtab->sh_size);

	fseek(file, strtab->sh_offset, SEEK_SET);
	fread(strings, strtab->sh_size, 1, file);

	//Read symbols
	Elf64_Sym *symbols = malloc(symtab->sh_size);
	
	fseek(file, symtab->sh_offset, SEEK_SET);
	fread(symbols, symtab->sh_size, 1, file);
	size_t symbol_count = symtab->sh_size/sizeof(Elf64_Sym);

	printf("\nMini Disassembly\n");
	printf("--------------------------------\n");

	for(size_t i = 0; i < symbol_count; i++)
	{

		Elf64_Sym *sym = &symbols[i];

		if(ELF64_ST_TYPE(sym->st_info) != STT_FUNC)
		{
			continue;
		}

		if(sym->st_shndx == SHN_UNDEF)
		{
			continue;
		}

		if(sym->st_size == 0)
		{
			continue;
		}

		const char *name = strings + sym->st_name;
		if(strlen(name) == 0)
		{
			continue;
		}

		printf("\n");
		printf("Function	: %s\n", name);
		printf("Address		: 0x%lx\n", sym->st_value);
		printf("Size		: %lu\n\n", sym->st_size);

		long file_offset = text->sh_offset + (sym->st_value - text->sh_addr);
		unsigned char *buffer = malloc(sym->st_size);

		if(buffer == NULL)
		{
			continue;
		}

		fseek(file, file_offset, SEEK_SET);
		fread(buffer, sym->st_size, 1, file);

		for(size_t j = 0; j < sym->st_size; j += 8)
		{
			printf("%08lx: ", sym->st_value + j);
			for(size_t k = 0; k < 8 && j + k < sym->st_size; k++)
			{
				printf("%02x ", buffer[j + k]);
			}
			printf("\n");
		}

		printf("\n");
		free(buffer);
	}

	free(symbols);
	free(strings);

cleanup:
	free(shstrings);
	free(sections);
	fclose(file);
}
