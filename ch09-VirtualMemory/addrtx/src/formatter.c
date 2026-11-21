#include <stdio.h>

#include "addrtx.h"

void print_translation(const address_info_t *info)
{	
	printf("\nAddress Translation\n");
	printf("====================================\n");
	printf("Virtual Address : 0x%lx\n", info->virtual_address);
	printf("Page Size	: %llu bytes\n\n", PAGE_SIZE);
	printf("VPN		: 0x%lx\n", info->vpn);
	printf("Offset		: 0x%lx\n", info->offset);
	printf("Offset decimal	: %lu\n\n", info->offset);
}
