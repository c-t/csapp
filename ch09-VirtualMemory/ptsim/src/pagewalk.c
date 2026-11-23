#include <stdio.h>

#include "ptsim.h"

void initialize_page_walk(page_walk_t *walk, const page_indices_t *idx)
{
    initialize_page_table(&walk->pml4);
    initialize_page_table(&walk->pdpt);
    initialize_page_table(&walk->pd);
    initialize_page_table(&walk->pt);
    populate_entry(&walk->pml4, idx->pml4, 0x1000);
    populate_entry(&walk->pdpt, idx->pdpt, 0x2000);
    populate_entry(&walk->pd, idx->pd, 0x3000);
    populate_entry(&walk->pt, idx->pt, 0x1000 + idx->pt);
}

int perform_page_walk(const page_walk_t *walk, const page_indices_t *idx, uint64_t *frame)
{
    if (!walk->pml4.entries[idx->pml4].present)
    {
        return 0;
    }

    if (!walk->pdpt.entries[idx->pdpt].present)
    {
        return 0;
    }

    if (!walk->pd.entries[idx->pd].present)
    {
        return 0;
    }

    if (!walk->pt.entries[idx->pt].present)
    {
        return 0;
    }

    *frame = walk->pt.entries[idx->pt].frame;

    return 1;
}

void print_page_walk(const page_walk_t *walk, const page_indices_t *idx)
{
    uint64_t frame;

    printf("\nPage Walk Simulation\n");
    printf("====================================\n\n");
    printf("Lookup PML4[%u] ... OK\n", idx->pml4);
    printf("Lookup PDPT[%u] ... OK\n", idx->pdpt);
    printf("Lookup PD[%u] ... OK\n", idx->pd);
    printf( "Lookup PT[%u] ... OK\n", idx->pt);

    if (perform_page_walk(walk, idx, &frame))
    { 
        printf("\nFrame Found : 0x%lx\n", frame);
    }
    else
    {
        printf("\nPage Fault\n");
    }

    printf("\n");
}

uint64_t get_frame(const page_walk_t *walk, const page_indices_t *idx)
{
    return walk->pt.entries[idx->pt].frame;
}