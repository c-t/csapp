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

static void print_bits(uint64_t value, int bits)
{
    for (int i = bits - 1; i >= 0; i--)
    {
        printf("%d", (int)((value >> i) & 1));
    }
}

void print_visualization(const page_indices_t *idx)
{
    uint64_t address = idx->virtual_address;

    printf("\nAddress Visualization\n");
    printf("====================================\n\n");
    printf("| PML4 | PDPT |  PD  |  PT  | OFFSET |\n\n");

    for (int i = 47; i >= 0; i--)
    {
        if (i == 38 || i == 29 || i == 20 || i == 11)
        {
            printf("|");
        }

        printf("%d", (int)((address >> i) & 1));
    }

    printf("\n\n");

    printf("PML4   : ");
    print_bits(idx->pml4, 9);
    printf("\n");

    printf("PDPT   : ");
    print_bits( idx->pdpt, 9);
    printf("\n");

    printf("PD     : ");
    print_bits( idx->pd, 9);
    printf("\n");

    printf("PT     : ");
    print_bits( idx->pt, 9);
    printf("\n");

    printf("OFFSET : ");
    print_bits(idx->offset, 12);
    printf("\n\n");
}

void print_page_table_structure(const page_indices_t *idx)
{
    printf("\nPage Table Structure\n");
    printf("====================================\n\n");
    printf("PML4[%u]\n", idx->pml4);
    printf("  ↓\n");
    printf("PDPT[%u]\n", idx->pdpt);
    printf("  ↓\n");
    printf("PD[%u]\n", idx->pd);
    printf("  ↓\n");
    printf("PT[%u]\n", idx->pt);
    printf("  ↓\n");
    printf("FRAME\n\n");
}