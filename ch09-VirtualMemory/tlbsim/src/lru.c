#include <stdio.h>

#include "tlbsim.h"

void lru_insert(tlb_t *tlb, uint64_t vpn, uint64_t frame)
{
    int victim = 0;
	uint64_t oldest = tlb->entries[0].last_used;

    for (int i = 1; i < SIM_TLB_SIZE; i++)
    {
        if (tlb->entries[i].last_used < oldest)
		{
            oldest = tlb->entries[i].last_used;
            victim = i;
        }
    }

    printf("LRU Evicting Entry %d", victim);

    if (tlb->entries[victim].valid)
    {
        printf(" (VPN 0x%lx)", tlb->entries[victim].vpn);
    }

    printf("\n");
	
    tlb->entries[victim].vpn = vpn;
    tlb->entries[victim].frame = frame;
    tlb->entries[victim].valid = 1;
    tlb->access_counter++;
    tlb->entries[victim].last_used = tlb->access_counter;
}

void run_lru_demo(tlb_t *tlb)
{
    printf("\n");
    printf("LRU Replacement Demo\n");
    printf("====================================\n\n");

    lru_insert(tlb, 0xAAA, simulate_page_walk(0xAAA));
    lru_insert(tlb, 0xBBB, simulate_page_walk(0xBBB));
    lru_insert(tlb, 0xCCC, simulate_page_walk(0xCCC));
    lru_insert(tlb, 0xDDD, simulate_page_walk(0xDDD));

    uint64_t frame;
    tlb_lookup(tlb, 0xAAA, &frame);
    tlb_lookup(tlb, 0xAAA, &frame);
    tlb_lookup(tlb, 0xBBB, &frame);

    printf("\nRecent accesses: AAA AAA BBB\n\n");
    lru_insert(tlb, 0xEEE, simulate_page_walk(0xEEE));

    printf("\nFinal LRU State\n");
    printf("====================================\n\n");
    printf("%-8s %-12s %-12s %-12s\n", "Entry", "VPN", "Frame", "LastUsed");
    printf("------------------------------------------------\n");

    for (int i = 0; i < SIM_TLB_SIZE; i++)
    {
        printf("%-8d 0x%-10lx 0x%-10lx %-12lu\n", i, tlb->entries[i].vpn, tlb->entries[i].frame, tlb->entries[i].last_used);
    }

    printf("\n");
}