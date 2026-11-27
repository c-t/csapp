#include <assert.h>

#include "cachesim.h"

int main(void)
{
    cache_t cache;
    initialize_cache(&cache);

    cache_address_t a;
    decode_address(0x00000000, &a);
    assert(cache_lookup(&cache, &a) == 0);

    fifo_fill(&cache, &a);
    assert(cache_lookup(&cache, &a) == 1);

    cache_address_t b;
    decode_address(0x00000100, &b);
    assert(cache_lookup(&cache, &b) == 0);
    fifo_fill(&cache, &b);

    assert(cache.statistics.accesses == 3);
    assert(cache.statistics.hits == 1);
    assert(cache.statistics.misses == 2);
    assert(cache.statistics.evictions == 0);

    for (uint32_t address = 0x00000200;
         address <= 0x00000500;
         address += 0x100)
    {
        cache_address_t decoded;
        decode_address(address, &decoded);
        if (!cache_lookup(&cache, &decoded))
        {
            fifo_fill(&cache, &decoded);
        }
    }

    assert(cache.statistics.accesses == 7);
    assert(cache.statistics.hits == 1);
    assert(cache.statistics.misses == 6);
    assert(cache.statistics.evictions == 2);

    return 0;
}
