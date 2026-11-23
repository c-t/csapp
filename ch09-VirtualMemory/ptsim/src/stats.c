#include <stdio.h>
#include <stdint.h>

#include "ptsim.h"

void print_translation_statistics(void)
{
    uint64_t addresses[] =
    {
        0x7ffff84e371cULL,
        0x7ffff84e3720ULL,
        0x7ffff84e4000ULL,
        0x58dc74280010ULL
    };

    size_t count = sizeof(addresses) / sizeof(addresses[0]);

    uint64_t frames[16];
    size_t unique = 0;

    for (size_t i = 0; i < count; i++)
    {
        page_indices_t idx;
        extract_indices(addresses[i], &idx);

        page_walk_t walk;
        initialize_page_walk(&walk, &idx);

        uint64_t frame = get_frame(&walk, &idx);
        int found = 0;
        for (size_t j = 0; j < unique; j++)
        {
            if (frames[j] == frame)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            frames[unique++] = frame;
        }
    }

    translation_stats_t stats;
    stats.total_translations = count;
    stats.unique_frames = unique;
    stats.shared_frames = count - unique;
    stats.utilization = ((double)unique / (double)count) * 100.0;

    printf("\nTranslation Statistics\n");
    printf("====================================\n\n");
    printf("Total Translations : %zu\n", stats.total_translations);
    printf( "Unique Frames      : %zu\n", stats.unique_frames);
    printf("Shared Frames      : %zu\n", stats.shared_frames);
    printf("Frame Utilization  : %.2f%%\n", stats.utilization);
    printf("\n");
}