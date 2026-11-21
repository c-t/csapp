#ifndef ADDRTX_H
#define	ADDRTX_H

#include <stdint.h>

#definee PAGE_SIZE 4096ULL

typedef struct
{
	uint64_t address;
	uint64_t vpn;
	uint64_t offset;
} addr_info_t;

void translate_address(uint64_t address, addr_info_t *info);
void print_translation(const addr_info_t *info);

#endif
