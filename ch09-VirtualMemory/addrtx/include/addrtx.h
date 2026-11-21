#ifndef ADDRTX_H
#define	ADDRTX_H

#include <stdint.h>

#define PAGE_SIZE 4096ULL
#define PAGE_OFFSET_MASK 0xFFFULL

typedef struct
{
	uint64_t virtual_address;
	uint64_t vpn;
	uint64_t offset;
} address_info_t;

typedef enum
{
	REGION_UNKNOWN,
	REGION_STACK,
	REGION_HEAP_DATA
} region_type_t;

void translate_address(uint64_t address, address_info_t *info);
void print_translation(const address_info_t *info);
void print_binary_visualization(const address_info_t *info);
void print_binary_split(const address_info_t *info);
region_type_t classify_address(uint64_t address);
const char* region_name(region_type_t region);
void print_classification(uint64_t address);

#endif
