#include <stdio.h>

#include "tlbsim.h"

void run_access_pattern(tlb_t *tlb)
{
    uint64_t accesses[] =
    {
        0xAAA,
        0xBBB,
        0xAAA,
        0xAAA,
        0xBBB
    };

	int hits = 0;
	int misses = 0;
    size_t count = sizeof(accesses) / sizeof(accesses[0]);

    printf("\nRepeated Access Pattern\n");
    printf("====================================\n\n");

    printf("%-10s %-10s %-10s\n","VPN","Result","Frame");
    printf("------------------------------------\n");

    for (size_t i = 0; i < count; i++)
    {
        uint64_t frame;
        int hit = tlb_lookup(tlb, accesses[i], &frame);
		
		if (hit)
		{
			hits++;
		}
		else
        {
			misses++;
            frame = simulate_page_walk(accesses[i]);
            insert_translation(tlb, accesses[i], frame);
        }

        printf("0x%-8lx %-10s 0x%lx\n", accesses[i], hit ? "HIT" : "MISS", frame);
    }

	double hit_rate = ((double)hits / (double)count) * 100.0;
	double miss_rate = ((double)misses / (double)count) * 100.0;

	printf("Pattern Statistics\n");
	printf("====================================\n\n");
	printf("Total Accesses : %zu\n", count);
	printf("Hits           : %d\n", hits);
	printf("Misses         : %d\n", misses);
	printf("Hit Rate       : %.2f%%\n", hit_rate);
	printf("Miss Rate      : %.2f%%\n",miss_rate);
	printf("\n");
}