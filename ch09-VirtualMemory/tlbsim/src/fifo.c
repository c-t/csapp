#include <stdio.h>

#include "tlbsim.h"

void run_fifo_demo(tlb_t *tlb)
{
    uint64_t vpns[] =
    {
        0xAAA,
        0xBBB,
        0xCCC,
        0xDDD,
        0xEEE
    };

    size_t count = sizeof(vpns) / sizeof(vpns[0]);

    printf("\nFIFO Replacement Demo\n");
    printf("====================================\n\n");

    for (size_t i = 0; i < count; i++)
    {
        uint64_t frame = simulate_page_walk(vpns[i]);
        fifo_insert(tlb, vpns[i], frame);
        printf("Inserted VPN 0x%lx -> Frame 0x%lx\n", vpns[i], frame);
    }

    printf("\nFinal FIFO TLB State\n");
    printf("====================================\n\n");
    printf("%-8s %-12s %-12s\n", "Entry", "VPN", "Frame");
    printf("------------------------------------\n");

    for (int i = 0; i < SIM_TLB_SIZE; i++)
    {
        printf("%-8d 0x%-10lx 0x%-10lx\n", i, tlb->entries[i].vpn, tlb->entries[i].frame);
    }

    printf("\n");
}