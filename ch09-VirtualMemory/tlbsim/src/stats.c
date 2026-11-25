#include <stdio.h>

#include "tlbsim.h"

static void initialize_stats(tlb_stats_t *stats)
{
    stats->accesses = 0;
    stats->hits = 0;
    stats->misses = 0;
    stats->fills = 0;
    stats->evictions = 0;
    stats->hit_rate = 0.0;
    stats->miss_rate = 0.0;
}

static void print_stats(const char *name, tlb_stats_t *stats)
{
    stats->hit_rate = ((double)stats->hits / stats->accesses) * 100.0;
    stats->miss_rate = ((double)stats->misses / stats->accesses) * 100.0;

    printf("\n%s Statistics\n", name);
    printf("====================================\n\n");
    printf("Accesses  : %d\n", stats->accesses);
    printf("Hits      : %d\n", stats->hits);
    printf("Misses    : %d\n", stats->misses);
    printf("Fills     : %d\n", stats->fills);
    printf("Evictions : %d\n", stats->evictions);
    printf("Hit Rate  : %.2f%%\n", stats->hit_rate);
    printf("Miss Rate : %.2f%%\n", stats->miss_rate);
    printf("\n");
}


static void run_fifo_stats(tlb_stats_t *stats)
{
    tlb_t tlb;

    initialize_tlb(&tlb);

    uint64_t workload[] =
    {
        0xAAA,
        0xBBB,
        0xCCC,
        0xDDD,
        0xAAA,
        0xBBB,
        0xEEE,
        0xAAA,
        0xBBB,
        0xFFF
    };

    size_t count = sizeof(workload) / sizeof(workload[0]);

    for (size_t i = 0; i < count; i++)
    {
        uint64_t frame;

        stats->accesses++;

        int hit = tlb_lookup(&tlb, workload[i], &frame);

        if (hit)
        {
            stats->hits++;
        }
        else
        {
            stats->misses++;
            frame = simulate_page_walk(workload[i]);
            if (i >= SIM_TLB_SIZE)
            {
                stats->evictions++;
                fifo_insert(&tlb, workload[i], frame, 0);
            }
            else
            {
                insert_translation(&tlb, workload[i], frame);
            }
            stats->fills++;
        }
    }
}

static void run_lru_stats(tlb_stats_t *stats)
{
    tlb_t tlb;
    initialize_tlb(&tlb);

    uint64_t workload[] =
    {
        0xAAA,
        0xBBB,
        0xCCC,
        0xDDD,
        0xAAA,
        0xBBB,
        0xEEE,
        0xAAA,
        0xBBB,
        0xFFF
    };

    size_t count = sizeof(workload) / sizeof(workload[0]);

    for (size_t i = 0; i < count; i++)
    {
        uint64_t frame;
        stats->accesses++;
        int hit = tlb_lookup( &tlb, workload[i], &frame);
        if (hit)
        {
            stats->hits++;
        }
        else
        {
            stats->misses++;
            frame = simulate_page_walk(workload[i]);
            if (i >= SIM_TLB_SIZE)
            {
                stats->evictions++;
                lru_insert(&tlb, workload[i], frame);
            }
            else
            {
                insert_translation(&tlb,  workload[i], frame);
            }
            stats->fills++;
        }
    }
}

void run_statistics_demo(void)
{
    tlb_stats_t fifo_stats;
    tlb_stats_t lru_stats;

    initialize_stats(&fifo_stats);
    initialize_stats(&lru_stats);
    run_fifo_stats(&fifo_stats);
    run_lru_stats(&lru_stats);
    print_stats("FIFO", &fifo_stats);
    print_stats("LRU", &lru_stats);
}
