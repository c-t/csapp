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

void run_temporal_locality_demo(void)
{
    cache_t cache;
    initialize_cache(&cache);

    printf("\nTemporal Locality Demo\n");
    printf("====================================\n\n");

    uint32_t addresses[] =
    {
        0x00000000,
        0x00000100,
        0x00000000,
        0x00000000,
        0x00000100,
        0x00000000
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

void run_spatial_locality_demo(void)
{
    cache_t cache;
    initialize_cache(&cache);

    printf("\nSpatial Locality Demo\n");
    printf("====================================\n\n");

    for (uint32_t address = 0x00000000;
         address <= 0x00000010;
         address += 4)
    {
        cache_address_t decoded;
        decode_address(address, &decoded);
        int hit = cache_lookup(&cache, &decoded);
        printf("Access 0x%08x : %s\n", address, hit ? "HIT" : "MISS");
        if (!hit)
        {
            lru_fill(&cache, &decoded);
        }
    }

    print_statistics(&cache);
}

void run_locality_demo(void)
{
    run_temporal_locality_demo();
    run_spatial_locality_demo();
}

void print_help(const char *program_name)
{
    printf("CacheSim v%s\n", CACHESIM_VERSION);
    printf("Usage: %s <address>|fifo|lru|temporal|spatial|locality|all|help|version\n", program_name);
    printf("\nModes:\n");
    printf("  <hex-address>  Decompose and lookup one address\n");
    printf("  fifo           Run the FIFO replacement demo\n");
    printf("  lru            Run the LRU replacement demo\n");
    printf("  temporal       Run the temporal locality demo\n");
    printf("  spatial        Run the spatial locality demo\n");
    printf("  locality       Run both locality demos\n");
    printf("  all            Run the FIFO, LRU, and locality demos\n");
    printf("  help           Print this usage message\n");
    printf("  version        Print the CacheSim version\n");
}

void print_version(void)
{
    printf("CacheSim v%s\n", CACHESIM_VERSION);
}

void run_all_demos(void)
{
    run_fifo_demo();
    run_lru_demo();
    run_temporal_locality_demo();
    run_spatial_locality_demo();
}