#ifndef ADDRTX_H
#define	ADDRTX_H

#include <stddef.h>
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

typedef struct
{
	uint64_t page_size;
	uint64_t vpn;
	uint64_t offset;
	int offset_bits;
} page_translation_t;

typedef struct
{
	uint64_t address;
	uint64_t vpn;
} address_entry_t;

void translate_address(uint64_t address, address_info_t *info);
void print_translation(const address_info_t *info);
void print_binary_visualization(const address_info_t *info);
void print_binary_split(const address_info_t *info);
region_type_t classify_address(uint64_t address);
const char* region_name(region_type_t region);
void print_classification(uint64_t address);
void print_page_size_analysis(uint64_t address);
void analyze_addresses(uint64_t *addresses, size_t count);

#endif
