#include <stdio.h>

#include "cachesim.h"

void initialize_cache(cache_t *cache)
{
    for (int set = 0; set < CACHE_SETS; set++)
    {
        cache->fifo_victim[set] = 0;
        for (int way = 0; way < CACHE_WAYS; way++)
        {
            cache->sets[set].lines[way].tag = 0;
            cache->sets[set].lines[way].age = 0;
            cache->sets[set].lines[way].valid = 0;
        }
    }
    cache->timestamp = 0;
    reset_statistics(cache);
}

void reset_statistics(cache_t *cache)
{
    cache->statistics.accesses = 0;
    cache->statistics.hits = 0;
    cache->statistics.misses = 0;
    cache->statistics.evictions = 0;
}

void record_cache_lookup(cache_t *cache, int hit)
{
    cache->statistics.accesses++;
    if (hit)
    {
        cache->statistics.hits++;
    }
    else
    {
        cache->statistics.misses++;
    }
}

void record_eviction(cache_t *cache)
{
    cache->statistics.evictions++;
}

void print_statistics(const cache_t *cache)
{
    double hit_rate = cache->statistics.accesses == 0
                          ? 0.0
                          : 100.0 * (double)cache->statistics.hits /
                                (double)cache->statistics.accesses;
    double miss_rate = cache->statistics.accesses == 0
                           ? 0.0
                           : 100.0 * (double)cache->statistics.misses /
                                 (double)cache->statistics.accesses;

    printf("\nCache Statistics\n");
    printf("====================================\n\n");
    printf("Total Accesses : %llu\n", (unsigned long long)cache->statistics.accesses);
    printf("Hits           : %llu\n", (unsigned long long)cache->statistics.hits);
    printf("Misses         : %llu\n", (unsigned long long)cache->statistics.misses);
    printf("Evictions      : %llu\n", (unsigned long long)cache->statistics.evictions);
    printf("Hit Rate       : %.2f%%\n", hit_rate);
    printf("Miss Rate      : %.2f%%\n", miss_rate);
    printf("\n");
}

void print_cache(const cache_t *cache)
{
    printf("\nCache Structure\n");
    printf("====================================\n\n");
    printf("%-8s %-6s %-12s %-8s %-8s\n", "Set", "Way", "Tag", "Valid", "Age");
    printf("--------------------------------------------------\n");
    for (int set = 0; set < CACHE_SETS; set++)
    {
        for (int way = 0; way < CACHE_WAYS; way++)
        {
            const cache_line_t *line = &cache->sets[set].lines[way];
            printf("%-8d %-6d 0x%-10x %-8s %-8llu\n",
                   set, way, line->tag,
                   line->valid ? "yes" : "no",
                   (unsigned long long)line->age);
        }
    }
    printf("\n");
}

void populate_cache_line(cache_t *cache, uint32_t set, uint32_t tag)
{
    cache_set_t *cache_set = &cache->sets[set];
    for (int way = 0; way < CACHE_WAYS; way++)
    {
        if (!cache_set->lines[way].valid)
        {
            cache_set->lines[way].tag = tag;
            cache_set->lines[way].valid = 1;
            return;
        }
    }

    uint32_t victim = cache->fifo_victim[set];
    record_eviction(cache);
    cache_set->lines[victim].tag = tag;
    cache_set->lines[victim].valid = 1;
    cache->fifo_victim[set] = (victim + 1) % CACHE_WAYS;
}

int cache_lookup(cache_t *cache, const cache_address_t *address)
{
    cache_set_t *set = &cache->sets[address->set];
    for (int way = 0; way < CACHE_WAYS; way++)
    {
        cache_line_t *line = &set->lines[way];
        if (line->valid && line->tag == address->tag)
        {
            cache->timestamp++;
            line->age = cache->timestamp;
            record_cache_lookup(cache, 1);
            return 1;
        }
    }
    record_cache_lookup(cache, 0);
    return 0;
}

void print_lookup_result(const cache_address_t *address, int hit)
{
    printf("\nCache Lookup\n");
    printf("====================================\n\n");
    printf("Tag    : 0x%x\n", address->tag);
    printf("Set    : %u\n\n", address->set);
    printf("Result : %s\n", hit ? "CACHE HIT" : "CACHE MISS");
    printf("\n");
}

void cache_fill(cache_t *cache, const cache_address_t *address)
{
    cache_set_t *set = &cache->sets[address->set];

    for (int way = 0; way < CACHE_WAYS; way++)
    {
        if (!set->lines[way].valid)
        {
            cache->timestamp++;
            set->lines[way].tag = address->tag;
            set->lines[way].age = cache->timestamp;
            set->lines[way].valid = 1;
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

    record_eviction(cache);
    cache->timestamp++;
    set->lines[victim].tag = address->tag;
    set->lines[victim].age = cache->timestamp;
    set->lines[victim].valid = 1;
}

void print_fill_result(const cache_address_t *address)
{
    printf("\nCache Fill\n");
    printf("====================================\n\n");
    printf("Set    : %u\n", address->set);
    printf("Tag    : 0x%x\n\n", address->tag);
    printf("Block inserted into cache\n\n");
}