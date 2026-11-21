#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "addrtx.h"

uint64_t addresses[] = 
{
	0x61d31f84a010ULL,
	0x61d34150f010ULL,
	0x7fff4ca70d90ULL,
	0x7fff4ca70d8cULL
};

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
	print_page_size_analysis(info.virtual_address);
	print_region(info.virtual_address);
	print_self_regions();
	analyze_addresses(addresses, sizeof(addresses)/sizeof(addresses[0]));
	
	return 0;
}
