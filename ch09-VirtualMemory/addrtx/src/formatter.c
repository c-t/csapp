#include <stdio.h>

#include "addrtx.h"

static void print_bits(uint64_t value, int bits)
{
	for(int i = bits - 1; i >= 0; i--)
	{
		printf("%d", (int)((value>>i)&1));
	}
}

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

void print_binary_visualization(const address_info_t *info)
{
	printf("\nBinary layout\n");
	printf("-----------------------------\n");
	printf("VPN (%d bits)\n\n", 52);
	print_bits(info->vpn, 52);
	printf("\n\nOffset (12 bits)\n\n");
	print_bits(info->offset, 12);
	printf("\n\n");
}

void print_binary_split(const address_info_t *info)
{
	uint64_t address = info->virtual_address;

	printf("Visual Split\n");
	printf("===================================\n\n");
	printf("|<-------VPN------>|<-OFFSET->|\n");
	for(int i = 47; i >= 0; i--)
	{
		if(i==11)
		{
			printf("|");
		}
		printf("%d", (int)((address >> i ) & 1));
	}

	printf("\n\n");
}

void print_classification(uint64_t address)
{
	region_type_t region = classify_address(address);
	printf("\nAddress Classification\n");
	printf("===================================\n\n");
	printf("Address	: 0x%lx\n", address);
	printf("Region	: %s\n", region_name(region));
	printf("\n");
}
