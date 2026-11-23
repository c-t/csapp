#include <stdio.h>

#include "ptsim.h"

void print_indices(const page_indices_t *idx)
{
    printf("\nPage Table Indices\n");
    printf("====================================\n\n");
    printf("Virtual Address : 0x%lx\n\n", idx->virtual_address);
    printf("PML4 Index      : %u\n", idx->pml4);
    printf("PDPT Index      : %u\n", idx->pdpt);
    printf("PD Index        : %u\n", idx->pd);
    printf("PT Index        : %u\n", idx->pt);
    printf("Offset          : 0x%x\n", idx->offset);
    printf("\n");
}