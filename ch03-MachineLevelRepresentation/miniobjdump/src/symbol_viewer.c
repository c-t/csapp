#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miniobjdump.h"

void print_symbols(const char* filename, const Elf64_Ehdr *header)
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

	for(int i = 0; i < header->e_shnum; i++)
	{
		if(sections[i].sh_type == SHT_SYMTAB)
		{
			symtab = &sections[i];
			strtab = &sections[sections[i].sh_link];
			break;
		}
	}

	if(symtab == NULL || strtab == NULL)
	{
		goto cleanup;
	}

	char *strings = malloc(strtab->sh_size);

	fseek(file, strtab->sh_offset, SEEK_SET);
	fread(strings, strtab->sh_size, 1, file);

	size_t count = symtab->sh_size/sizeof(Elf64_Sym);
	
	Elf64_Sym *symbols = malloc(symtab->sh_size);
	
	fseek(file, symtab->sh_offset, SEEK_SET);
	fread(symbols, symtab->sh_size, 1, file);

	printf("\nSymbols\n");
	printf("--------------------------------\n");
	for(size_t i = 0; i < count; i++)
	{
		const char *name = strings + symbols[i].st_name;

		if(strlen(name) == 0)
		{
			continue;
		}
		
		printf("%016lx %s\n", symbols[i].st_value, name);
	}

	printf("\n");

	free(symbols);
	free(strings);

cleanup:
	free(sections);
	fclose(file);
}
