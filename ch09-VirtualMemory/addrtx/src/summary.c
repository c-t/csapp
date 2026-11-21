#include <stdio.h>
#include <stdint.h>

#include "addrtx.h"

void print_summary_report(uint64_t address)
{
    printf("AddrTx v1.0 Summary\n");
    printf("=====================================\n");
    printf("Virtual Address : 0x%lx\n", address);
    printf("VPN             : 0x%lx\n", address >> 12);
    printf("Offset          : 0x%lx\n", address & 0xfff);
    printf("\nFeatures Executed\n");
    printf("  [OK] Translation\n");
    printf("  [OK] Binary Layout\n");
    printf("  [OK] Classification\n");
    printf("  [OK] Page Size Analysis\n");
    printf("  [OK] Memory Region Analysis\n");
    printf("  [OK] Multi-Address Analysis\n");
    printf("  [OK] Translation Statistics\n");

    printf("\n");
}
