#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cachesim.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <hex-address>|fifo|lru|temporal|spatial|locality\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "fifo") == 0)
    {
        run_fifo_demo();
        return 0;
    }

    if (strcmp(argv[1], "lru") == 0)
    {
        run_lru_demo();
        return 0;
    }

    if (strcmp(argv[1], "temporal") == 0)
    {
        run_temporal_locality_demo();
        return 0;
    }

    if (strcmp(argv[1], "spatial") == 0)
    {
        run_spatial_locality_demo();
        return 0;
    }

    if (strcmp(argv[1], "locality") == 0)
    {
        run_locality_demo();
        return 0;
    }

    char *end = NULL;
    unsigned long parsed = strtoul(argv[1], &end, 0);
    if (argv[1][0] == '\0' || *end != '\0')
    {
        printf("Invalid address: %s\n", argv[1]);
        return 1;
    }

    uint32_t address = (uint32_t)parsed;

    cache_address_t decoded;
    decode_address(address, &decoded);
    print_address_info(&decoded);

    cache_t cache;
    initialize_cache(&cache);
    print_cache(&cache);

    int hit = cache_lookup(&cache, &decoded);
    print_lookup_result(&decoded, hit);

    if (!hit)
    {
        cache_fill(&cache, &decoded);
        print_fill_result(&decoded);
    }

    hit = cache_lookup(&cache, &decoded);
    print_lookup_result(&decoded, hit);

    print_cache(&cache);

    return 0;
}