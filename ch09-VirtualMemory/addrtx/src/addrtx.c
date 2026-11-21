#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "addrtx.h"

int main(int argc, char* argv[])
{
	address_info_t info;

	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <virtual-address>\n", argv[0]);
		return EXIT_FAILURE;
	}

	uint64_t address = strtoull(argv[1], NULL, 0);
	translate_address(address, &info);
	print_translation(&info);
	print_binary_visualization(&info);
	print_binary_split(&info);
	print_classification(info.virtual_address);

	return 0;
}
