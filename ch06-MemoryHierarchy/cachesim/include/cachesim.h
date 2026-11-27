#ifndef CACHESIM_H
#define CACHESIM_H

#include <stdint.h>

#define ADDRESS_BITS 32

#define CACHE_SIZE_BYTES 1024
#define BLOCK_SIZE_BYTES 16
#define CACHE_WAYS 4

#define CACHE_LINES (CACHE_SIZE_BYTES / BLOCK_SIZE_BYTES)
#define CACHE_SETS (CACHE_LINES / CACHE_WAYS)

#define OFFSET_BITS 4
#define SET_BITS 4

#define TAG_BITS (ADDRESS_BITS - OFFSET_BITS - SET_BITS)

typedef struct
{
    uint32_t address;
    uint32_t tag;
    uint32_t set;
    uint32_t offset;
} cache_address_t;

typedef struct
{
    uint32_t tag;
    uint64_t age;
    int valid;
} cache_line_t;

typedef struct
{
    cache_line_t lines[CACHE_WAYS];
} cache_set_t;

typedef struct
{
    cache_set_t sets[CACHE_SETS];
    uint32_t fifo_victim[CACHE_SETS];
    uint64_t timestamp;
} cache_t;

void decode_address(uint32_t address, cache_address_t *result);
void print_address_info(const cache_address_t *address);
void initialize_cache(cache_t *cache);
void print_cache(const cache_t *cache);
int cache_lookup(cache_t *cache, const cache_address_t *address);
void populate_cache_line(cache_t *cache, uint32_t set, uint32_t tag);
void print_lookup_result(const cache_address_t *address, int hit);
void cache_fill(cache_t *cache, const cache_address_t *address);
void print_fill_result(const cache_address_t *address);
void fifo_fill(cache_t *cache, const cache_address_t *address);
void lru_fill(cache_t *cache, const cache_address_t *address);
void run_fifo_demo(void);
void run_lru_demo(void);

#endif