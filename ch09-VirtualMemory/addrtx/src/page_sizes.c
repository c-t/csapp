#include <stdio.h>
#include <stdint.h>

#include "addrtx.h"

static int offset_bits(uint64_t page_size)
{
	int bits = 0;

	while(page_size > 1)
	{
		bits++;
		page_size >>= 1;
	}

	return bits;
}

static void analyze(uint64_t address, uint64_t page_size)
{
	uint64_t original_page_size = page_size;

	int bits = offset_bits(page_size);

	uint64_t offset_mask = original_page_size - 1;
	uint64_t vpn = address >> bits;
	uint64_t offset = address & offset_mask;
	printf("Page size	: %lu\n", original_page_size);
	printf("Offset bits	: %d\n", bits);
	printf("VPN		: 0x%lx\n", vpn);
	printf("Offset		: 0x%lx\n", offset);
	printf("\n");
}

void print_page_size_analysis(uint64_t address)
{
	printf("\nPage Size Explorer\n");
	printf("===============================\n\n");
	printf("Address	: 0x%lx\n\n", address);
	printf("4 KB pages\n");
	printf("-------------------------------\n");
	analyze(address, 4096ULL);
	printf("2 MB pages\n");
	printf("-------------------------------\n");
	analyze(address, 2ULL * 1024 * 1024);
	printf("1 GB pages\n");
	printf("-------------------------------\n");
	analyze(address, 1024ULL * 1024 * 1024);
}
