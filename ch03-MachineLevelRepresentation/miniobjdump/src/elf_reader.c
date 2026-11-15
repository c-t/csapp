#include <stdio.h>
#include <stdlib.h>

#include "miniobjdump.h"

int read_elf_header(const char *filename, Elf64_Ehdr *header)
{
	FILE *file = fopen(filename, "rb");

	if(file == NULL)
	{
		perror("fopen");
		return -1;
	}

	if(fread(header, sizeof(Elf64_Ehdr), 1, file) != 1)
	{
		perror("fread");
		fclose(file);
		return -1;
	}

	fclose(file);

	return 0;
}
