#ifndef PTSIM_H
#define PTSIM_H

#include <stdint.h>

typedef struct
{
    uint64_t virtual_address;
    uint16_t pml4;
    uint16_t pdpt;
    uint16_t pd;
    uint16_t pt;
    uint16_t offset;
} page_indices_t;

void extract_indices(uint64_t address, page_indices_t *indices);
void print_indices(const page_indices_t *indices);
void print_visualization(const page_indices_t *indices);

#endif