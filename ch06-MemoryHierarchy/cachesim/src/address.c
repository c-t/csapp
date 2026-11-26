#include <stdio.h>

#include "cachesim.h"

void decode_address(uint32_t address, cache_address_t *result)
{
    result->address = address;
    result->offset = address & ((1U << OFFSET_BITS) - 1);
    result->set = (address >> OFFSET_BITS) & ((1U << SET_BITS) - 1);
    result->tag = address >> (OFFSET_BITS + SET_BITS);
}

void print_address_info(const cache_address_t *address)
{
    printf("\nCache Address Decomposition\n");
    printf("====================================\n\n");
    printf("Address : 0x%08x\n\n", address->address);
    printf("Tag     : %u (0x%x)\n", address->tag, address->tag);
    printf("Set     : %u (0x%x)\n", address->set, address->set);
    printf("Offset  : %u (0x%x)\n", address->offset, address->offset);
    printf("\n");
}