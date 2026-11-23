#include "ptsim.h"

#define INDEX_MASK 0x1FFULL

void extract_indices(uint64_t address, page_indices_t *indices)
{
    indices->virtual_address = address;
    indices->offset = address & 0xFFF;
    indices->pt = (address >> 12) & INDEX_MASK;
    indices->pd = (address >> 21) & INDEX_MASK;
    indices->pdpt = (address >> 30) & INDEX_MASK;
    indices->pml4 = (address >> 39) & INDEX_MASK;
}