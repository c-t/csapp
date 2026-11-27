#include <stdio.h>

#include "cachesim.h"

void lru_fill(cache_t *cache, const cache_address_t *address)
{
    cache_set_t *set = &cache->sets[address->set];

    for (int way = 0; way < CACHE_WAYS; way++)
    {
        if (!set->lines[way].valid)
        {
            cache->timestamp++;
            set->lines[way].tag = address->tag;
            set->lines[way].valid = 1;
            set->lines[way].age = cache->timestamp;
            printf("  LRU Fill: Set %u Way %d\n", address->set, way);
            return;
        }
    }

    int victim = 0;

    uint64_t oldest = set->lines[0].age;

    for (int way = 1; way < CACHE_WAYS; way++)
    {
        if (set->lines[way].age < oldest)
        {
            oldest = set->lines[way].age;
            victim = way;
        }
    }

    printf("  LRU Evict: Set %u Way %d Tag 0x%x\n", address->set, victim, set->lines[victim].tag);
    record_eviction(cache);
    cache->timestamp++;
    set->lines[victim].tag = address->tag;
    set->lines[victim].valid = 1;
    set->lines[victim].age = cache->timestamp;
}