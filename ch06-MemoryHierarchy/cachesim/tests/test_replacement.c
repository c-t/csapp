#include <assert.h>
#include <stdint.h>

#include "cachesim.h"

static cache_address_t decode(uint32_t address)
{
    cache_address_t result;
    decode_address(address, &result);
    return result;
}

int main(void)
{
    cache_t fifo;
    initialize_cache(&fifo);

    cache_address_t a = decode(0x00000000);
    cache_address_t b = decode(0x00000100);
    cache_address_t c = decode(0x00000200);

    fifo_fill(&fifo, &a);
    fifo_fill(&fifo, &b);
    fifo_fill(&fifo, &c);

    assert(fifo.sets[a.set].lines[0].valid);
    assert(fifo.sets[a.set].lines[1].valid);
    assert(fifo.sets[a.set].lines[2].valid);

    cache_address_t d = decode(0x00000300);
    fifo_fill(&fifo, &d);

    assert(fifo.sets[d.set].lines[3].tag == d.tag);
    assert(fifo.fifo_victim[d.set] == 0);

    cache_t lru;
    initialize_cache(&lru);

    cache_address_t one = decode(0x00000000);
    cache_address_t two = decode(0x00000100);
    cache_address_t three = decode(0x00000200);

    lru_fill(&lru, &one);
    lru_fill(&lru, &two);
    lru_fill(&lru, &three);

    cache_address_t four = decode(0x00000300);
    lru_fill(&lru, &four);

    assert(cache_lookup(&lru, &one) == 1);

    cache_address_t five = decode(0x00000400);
    lru_fill(&lru, &five);

    assert(cache_lookup(&lru, &one) == 1);
    assert(cache_lookup(&lru, &two) == 0);
    assert(cache_lookup(&lru, &three) == 1);
    assert(cache_lookup(&lru, &four) == 1);
    assert(cache_lookup(&lru, &five) == 1);

    return 0;
}