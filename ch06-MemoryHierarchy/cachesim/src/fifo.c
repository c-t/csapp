#include <stdio.h>

#include "cachesim.h"

void fifo_fill(cache_t *cache, const cache_address_t *address)
{
    cache_set_t *set = &cache->sets[address->set];

    for (int way = 0; way < CACHE_WAYS; way++)
    {
        if (!set->lines[way].valid)
        {
            set->lines[way].tag = address->tag;
            set->lines[way].valid = 1;
            cache->timestamp++;
            set->lines[way].age = cache->timestamp;
            printf("  FIFO Fill: Set %u Way %d\n", address->set, way);
            return;
        }
    }

    int victim = (int)cache->fifo_victim[address->set];
    printf("  FIFO Evict: Set %u Way %d Tag 0x%x\n",
           address->set, victim, set->lines[victim].tag);

    set->lines[victim].tag = address->tag;
    set->lines[victim].valid = 1;
    cache->timestamp++;
    set->lines[victim].age = cache->timestamp;
    cache->fifo_victim[address->set] = (uint32_t)((victim + 1) % CACHE_WAYS);
}