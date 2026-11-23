#include <stdio.h>

#include "ptsim.h"

void run_multi_translation(void)
{
    uint64_t addresses[] =
    {
        0x7ffff84e371cULL,
        0x7ffff84e3720ULL,
        0x7ffff84e4000ULL,
        0x58dc74280010ULL
    };

    size_t count = sizeof(addresses) / sizeof(addresses[0]);

    printf("\n");
    printf("Multi-Address Translation\n");
    printf("====================================\n\n");
    printf( "%-18s %-10s %-18s\n", "Virtual Address","Frame","Physical Address");
    printf("--------------------------------------------------\n");

    for (size_t i = 0; i < count; i++)
    {
        page_indices_t idx;
        extract_indices(addresses[i], &idx);

        page_walk_t walk;
        initialize_page_walk(&walk, &idx);

        uint64_t frame;
        perform_page_walk(&walk, &idx, &frame);

        translation_result_t result;
        generate_physical_address(frame, idx.offset, &result);
		
        printf("0x%-14lx 0x%-6lx 0x%lx\n", addresses[i], frame, result.physical_address);
    }

    printf("\n");
}