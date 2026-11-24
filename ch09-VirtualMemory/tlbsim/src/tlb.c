#include <stdio.h>

#include "tlbsim.h"

void initialize_tlb(tlb_t *tlb)
{
    for (int i = 0; i < TLB_ENTRIES; i++)
    {
        tlb->entries[i].vpn = 0;
        tlb->entries[i].frame = 0;
        tlb->entries[i].valid = 0;
    }
}

void populate_tlb_entry(tlb_t *tlb, int index, uint64_t vpn, uint64_t frame)
{
    if (index < 0 || index >= TLB_ENTRIES)
    {
        return;
    }

    tlb->entries[index].vpn = vpn;
    tlb->entries[index].frame = frame;
    tlb->entries[index].valid = 1;
}

void print_tlb(const tlb_t *tlb)
{
    printf("\nTLB Contents\n");
    printf("====================================\n\n");
    printf("%-8s %-12s %-12s %-8s\n", "Entry", "VPN", "Frame", "Valid");
    printf("--------------------------------------------\n");

    for (int i = 0; i < TLB_ENTRIES; i++)
    {
        printf("%-8d 0x%-10lx 0x%-10lx %-8s\n", i, tlb->entries[i].vpn, tlb->entries[i].frame, tlb->entries[i].valid ? "yes" : "no");
    }

    printf("\n");
}