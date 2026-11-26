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

void print_cache(
    const cache_t *cache)
{
    printf("\n");

    printf("Cache Structure\n");
    printf("====================================\n\n");

    printf(
        "%-8s %-12s %-8s\n",
        "Set",
        "Tag",
        "Valid");

    printf(
        "------------------------------------\n");

    for (int i = 0;
         i < CACHE_LINES;
         i++)
    {
        printf(
            "%-8d 0x%-10x %-8s\n",
            i,
            cache->sets[i].line.tag,
            cache->sets[i].line.valid
                ? "yes"
                : "no");
    }

    printf("\n");
}