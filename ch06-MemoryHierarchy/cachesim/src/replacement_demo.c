#include <stdio.h>

#include "cachesim.h"

void run_fifo_demo(void)
{
    cache_t cache;

    initialize_cache(&cache);
    printf("\nFIFO Replacement Demo\n");
    printf("====================================\n\n");

    uint32_t addresses[] =
    {
        0x00000000,
        0x00000100,
        0x00000200,
        0x00000300,
        0x00000400
    };

    for (size_t i = 0; i < 5; i++)
    {
        cache_address_t decoded;
        decode_address(addresses[i], &decoded);
        int hit = cache_lookup(&cache, &decoded);
        printf("Access 0x%08x : %s\n", addresses[i], hit ? "HIT" : "MISS");
        if (!hit)
        {
            fifo_fill(&cache, &decoded);
        }
    }

    print_statistics(&cache);
}

void run_lru_demo(void)
{
    cache_t cache;

    initialize_cache(&cache);
    printf("\nLRU Replacement Demo\n");
    printf("====================================\n\n");

    uint32_t addresses[] =
    {
        0x00000000,
        0x00000100,
        0x00000200,
        0x00000300,
        0x00000000,
        0x00000400
    };

    for (size_t i = 0; i < 6; i++)
    {
        cache_address_t decoded;
        decode_address(addresses[i], &decoded);
        int hit = cache_lookup(&cache, &decoded);
        printf("Access 0x%08x : %s\n", addresses[i], hit ? "HIT" : "MISS");
        if (!hit)
        {
            lru_fill(&cache, &decoded);
        }
    }

    print_statistics(&cache);
}