#include <stdio.h>

#include "cachesim.h"

void initialize_cache(cache_t *cache)
{
    for (int i = 0; i < CACHE_LINES; i++)
    {
        cache->sets[i].line.tag = 0;
        cache->sets[i].line.valid = 0;
    }
}

void print_cache(const cache_t *cache)
{
    printf("\nCache Structure\n");
    printf("====================================\n\n");
    printf("%-8s %-12s %-8s\n", "Set", "Tag", "Valid");
    printf("------------------------------------\n");
    for (int i = 0; i < CACHE_LINES; i++)
    {
        printf("%-8d 0x%-10x %-8s\n", i, cache->sets[i].line.tag, cache->sets[i].line.valid ? "yes" : "no");
    }
    printf("\n");
}

void populate_cache_line(cache_t *cache, uint32_t set, uint32_t tag)
{
    cache->sets[set].line.tag = tag;
    cache->sets[set].line.valid = 1;
}

int cache_lookup(const cache_t *cache, const cache_address_t *address)
{
    const cache_line_t *line = &cache->sets[address->set].line;
    if (!line->valid)
    {
        return 0;
    }
    if (line->tag == address->tag)
    {
        return 1;
    }
    return 0;
}

void print_lookup_result(const cache_address_t *address, int hit)
{
    printf("\nCache Lookup\n");
    printf("====================================\n\n");
    printf("Tag    : 0x%x\n", address->tag);
    printf("Set    : %u\n\n", address->set);
    printf("Result : %s\n",  hit ? "CACHE HIT" : "CACHE MISS");
    printf("\n");
}

void cache_fill(cache_t *cache, const cache_address_t *address)
{
    cache->sets[address->set].line.tag = address->tag;
    cache->sets[address->set].line.valid = 1;
}

void print_fill_result(const cache_address_t *address)
{
    printf("\nCache Fill\n");
    printf("====================================\n\n");
    printf("Set    : %u\n", address->set);
    printf("Tag    : 0x%x\n\n", address->tag);
    printf("Block inserted into cache\n\n");
}