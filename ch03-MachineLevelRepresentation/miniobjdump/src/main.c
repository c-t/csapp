#include <stdio.h>
#include <stdlib.h>

#include "miniobjdump.h"

int main(int argc, char *argv[])
{
	Elf64_Ehdr header;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	if(read_elf_header(argv[1], &header) != 0)
	{
		return EXIT_FAILURE;
	}

	print_elf_header(&header);
	print_sections(argv[1], &header);
	print_hex_dump(argv[1], &header, ".text");
	print_symbols(argv[1], &header);

	return EXIT_SUCCESS;
}
