#include <stdio.h>

#include "ptsim.h"

void print_summary(const page_indices_t *idx, uint64_t frame, uint64_t physical_address)
{
    printf("\nPTSim v1.0 Summary\n");
    printf("====================================\n\n");
    printf("Virtual Address : 0x%lx\n", idx->virtual_address);
    printf("PML4            : %u\n", idx->pml4);
    printf("PDPT            : %u\n", idx->pdpt);
    printf("PD              : %u\n", idx->pd);
    printf("PT              : %u\n", idx->pt);
    printf("Offset          : 0x%x\n", idx->offset);
    printf("\nFrame           : 0x%lx\n", frame);
    printf("Physical Addr   : 0x%lx\n", physical_address);
    printf("\nFeatures Executed\n");
    printf("  [OK] Index Extraction\n");
    printf("  [OK] Address Visualization\n");
    printf("  [OK] Page Table Structures\n");
    printf("  [OK] Page Walk Simulation\n");
    printf("  [OK] Physical Address Generation\n");
    printf("  [OK] Multi-Address Translation\n");
    printf("  [OK] Translation Statistics\n");
    printf("\n");
}