#include <elf.h>
#include <stdio.h>
#include <stdlib.h>

#include "miniobjdump.h"

void print_section_statistics(const char *filename, const Elf64_Ehdr *header)
{
	FILE *file = fopen(filename, "rb");

	if(file == NULL)
	{
		perror("fopen");
		return;
	}

	Elf64_Shdr *sections = malloc(sizeof(Elf64_Shdr) * header->e_shnum);

	if(sections == NULL)
	{
		fclose(file);
		return;
	}

	fseek(file, header->e_shoff, SEEK_SET);
	fread(sections, sizeof(Elf64_Shdr), header->e_shnum, file);

	Elf64_Shdr *shstr = &sections[header->e_shstrndx];

	char *strings = malloc(shstr->sh_size);

	if(strings == NULL)
	{
		free(sections);
		fclose(file);
		return;
	}
	
	fseek(file, shstr->sh_offset, SEEK_SET);
	fread(strings, shstr->sh_size, 1, file);

	printf("\nSection Statistics\n");
	printf("------------------------------------\n");
	printf("%-24s %12s\n", "Name", "Size");
	printf("------------------------------------\n");

	for(int i = 0; i < header->e_shnum; i++)
	{
		const char *name = strings + sections[i].sh_name;
		if(name[0] == '\0')
		{
			continue;
		}
		printf("%-24s %12lu\n", name, (unsigned long)sections[i].sh_size);
	}

	printf("\nTotal Sections: %u\n", header->e_shnum);

	printf("\n");
	free(strings);
	free(sections);
	fclose(file);
}
