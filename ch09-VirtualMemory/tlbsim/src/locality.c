#include <stdio.h>

#include "tlbsim.h"

static void reset_stats(tlb_stats_t *stats)
{
    stats->accesses = 0;
    stats->hits = 0;
    stats->misses = 0;
    stats->fills = 0;
    stats->evictions = 0;
}

static void run_sequential(tlb_stats_t *stats)
{
    tlb_t tlb;
    initialize_tlb(&tlb);

    uint64_t accesses[] =
    {
        0xAAA,
        0xAAA,
        0xAAA,
        0xAAA,
        0xAAA,
        0xAAA,
        0xAAA,
        0xAAA
    };

    size_t count = sizeof(accesses) / sizeof(accesses[0]);
    for (size_t i = 0; i < count; i++)
    {
        uint64_t frame;

        stats->accesses++;

        if (tlb_lookup(&tlb, accesses[i], &frame))
        {
            stats->hits++;
        }
        else
        {
            stats->misses++;
            frame = simulate_page_walk(accesses[i]);
            insert_translation(&tlb, accesses[i], frame);
            stats->fills++;
        }
    }
}

static void run_random(tlb_stats_t *stats)
{
    tlb_t tlb;
    initialize_tlb(&tlb);

    uint64_t accesses[] =
    {
        0xAAA,
        0xBBB,
        0xCCC,
        0xDDD,
        0xEEE,
        0xFFF,
        0x111,
        0x222
    };

    size_t count = sizeof(accesses) / sizeof(accesses[0]);
    for (size_t i = 0; i < count; i++)
    {
        uint64_t frame;
	
        stats->accesses++;
		
        if (tlb_lookup(&tlb, accesses[i], &frame))
        {
            stats->hits++;
        }
        else
        {
            stats->misses++;
            frame = simulate_page_walk(accesses[i]);
            insert_translation(&tlb, accesses[i], frame);
            stats->fills++;
        }
    }
}

static void print_locality_stats(const char *name, tlb_stats_t *stats)
{
    double hit_rate = ((double)stats->hits / stats->accesses) * 100.0;
    double miss_rate = ((double)stats->misses / stats->accesses) * 100.0;

    printf("%s\n", name);
    printf("------------------------------------\n");
    printf("Accesses : %d\n", stats->accesses);
    printf("Hits     : %d\n", stats->hits);
    printf("Misses   : %d\n", stats->misses);
    printf("Hit Rate : %.2f%%\n", hit_rate);
    printf("Miss Rate: %.2f%%\n\n", miss_rate);
}

void run_locality_experiments(void)
{
    tlb_stats_t sequential;
    tlb_stats_t random;

    reset_stats(&sequential);
    reset_stats(&random);
    run_sequential(&sequential);
    run_random(&random);

    printf("\nLocality Experiments\n");
    printf("====================================\n\n");
    print_locality_stats("Sequential Pattern", &sequential);
    print_locality_stats("Random Pattern", &random);
}