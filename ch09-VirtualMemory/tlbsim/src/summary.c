#include <stdio.h>

#include "tlbsim.h"

void print_tlbsim_summary(void)
{
    printf("\n");
    printf("TLBSim v1.0 Summary\n");
    printf("====================================\n\n");

    printf("Features Implemented\n\n");

    printf("  [OK] TLB Entry Structures\n");
    printf("  [OK] TLB Lookup\n");
    printf("  [OK] TLB Miss Handling\n");
    printf("  [OK] TLB Fill\n");
    printf("  [OK] Repeated Access Analysis\n");
    printf("  [OK] FIFO Replacement\n");
    printf("  [OK] LRU Replacement\n");
    printf("  [OK] Translation Statistics\n");
    printf("  [OK] Locality Experiments\n");

    printf("\n");

    printf("Key Learnings\n\n");

    printf("  • TLBs cache VPN-to-frame translations\n");
    printf("  • Hits avoid page walks\n");
    printf("  • Misses trigger translation work\n");
    printf("  • Cache replacement affects hit rate\n");
    printf("  • Locality strongly influences performance\n");

    printf("\n");

    printf("TLBSim v1.0 Complete\n\n");
}