#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "miniobjdump.h"

void print_hex_dump(const char* filename, const Elf64_Ehdr *header, const char *section_name)
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

	Elf64_Shdr *target = NULL;

	for(int i = 0; i < header->e_shnum; i++)
	{
		const char* name = strings + sections[i].sh_name;
		if(strcmp(name, section_name) == 0)
		{
			target = &sections[i];
			break;
		}
	}

	if (target == NULL)
	{
		printf("Section '%s' not found\n", section_name);
		goto cleanup;
	}

	unsigned char* buffer = malloc(target->sh_size);

	if(buffer == NULL)
	{
		goto cleanup;
	}

	fseek(file, target->sh_offset, SEEK_SET);
	fread(buffer, target->sh_size, 1, file);

	printf("\n%s Hex Dump\n", section_name);
	printf("--------------------------------\n");
	for(size_t i = 0; i < target->sh_size; i += 16)
	{
		printf("%08lx: ", target->sh_addr + i);
		for(size_t j = 0; j < 16 && i + j < target->sh_size; j++)
		{
			printf("%02x ", buffer[i + j]);
		}
		printf("\n");
	}

	printf("\n");

	free(buffer);

cleanup:
	free(strings);
	free(sections);
	fclose(file);
}
