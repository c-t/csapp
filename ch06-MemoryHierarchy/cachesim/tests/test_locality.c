#include <assert.h>
#include <stddef.h>

#include "cachesim.h"

int main(void)
{
    cache_t temporal;
    initialize_cache(&temporal);

    uint32_t temporal_addresses[] =
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
        decode_address(temporal_addresses[i], &decoded);
        if (!cache_lookup(&temporal, &decoded))
        {
            lru_fill(&temporal, &decoded);
        }
    }

    assert(temporal.statistics.accesses == 6);
    assert(temporal.statistics.hits == 4);
    assert(temporal.statistics.misses == 2);

    cache_t spatial;
    initialize_cache(&spatial);

    for (uint32_t address = 0x00000000;
         address <= 0x00000010;
         address += 4)
    {
        cache_address_t decoded;
        decode_address(address, &decoded);
        if (!cache_lookup(&spatial, &decoded))
        {
            lru_fill(&spatial, &decoded);
        }
    }

    assert(spatial.statistics.accesses == 5);
    assert(spatial.statistics.hits == 3);
    assert(spatial.statistics.misses == 2);
    assert(spatial.statistics.evictions == 0);

    return 0;
}
