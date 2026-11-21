#include <stdio.h>
#include <stdint.h>

#include "addrtx.h"

void print_translation_statistics(uint64_t *addresses, size_t count)
{
    uint64_t vpns[64];

    size_t unique = 0;

    for (size_t i = 0; i < count; i++)
    {
        uint64_t vpn = addresses[i] >> 12;

        int found = 0;

        for (size_t j = 0; j < unique; j++)
        {
            if (vpns[j] == vpn)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            vpns[unique++] = vpn;
        }
    }

    printf("\nTranslation Statistics\n");
    printf("=====================================\n\n");

    printf("Total Addresses 	: %zu\n", count);
    printf("Unique VPNs     	: %zu\n", unique);
    printf("Shared Pages    	: %zu\n", count - unique);

    double utilization = ((double)unique/(double)count)*100.0;
    printf("Page Utilization	: %.2f%%\n", utilization);

    printf("\n");
}
