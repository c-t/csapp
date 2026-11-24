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

int tlb_lookup(const tlb_t *tlb, uint64_t vpn, uint64_t *frame)
{
    for (int i = 0; i < TLB_ENTRIES; i++)
    {
        if (!tlb->entries[i].valid)
        {
            continue;
        }

        if (tlb->entries[i].vpn == vpn)
        {
            *frame = tlb->entries[i].frame;
            return 1;
        }
    }

    return 0;
}

void print_lookup_result(uint64_t vpn, int hit, uint64_t frame)
{
    printf("\nTLB Lookup\n");
    printf("====================================\n\n");
    printf("VPN : 0x%lx\n\n", vpn);

    if (hit)
    {
        printf("Result : HIT\n");
        printf("Frame  : 0x%lx\n", frame);
    }
    else
    {
        printf("Result : MISS\n");
    }

    printf("\n");
}

uint64_t simulate_page_walk(uint64_t vpn)
{
    return 0x1000 + (vpn & 0xFFF);
}

int insert_translation(tlb_t *tlb, uint64_t vpn, uint64_t frame)
{
    for (int i = 0; i < TLB_ENTRIES; i++)
    {
        if (!tlb->entries[i].valid)
        {
            tlb->entries[i].vpn = vpn;
            tlb->entries[i].frame = frame;
            tlb->entries[i].valid = 1;

            return i;
        }
    }

    return -1;
}

void print_fill_result(uint64_t vpn, uint64_t frame)
{
    printf("\nTLB Fill\n");
    printf("====================================\n\n");
    printf("VPN   : 0x%lx\n", vpn);
    printf("Frame : 0x%lx\n", frame);
    printf("\nInserted Into TLB\n\n");
}