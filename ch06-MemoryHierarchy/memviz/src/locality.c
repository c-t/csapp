#include "memviz.h"
#include <stdio.h>

void analyze_address(uint64_t address, address_info_t *info)
{
    info->address = address;
    info->page_number = address / PAGE_SIZE;
    info->page_offset = address % PAGE_SIZE;
    info->cache_line = address / CACHE_LINE_SIZE;
    info->cache_offset = address % CACHE_LINE_SIZE;
}

void analyze_spatial_locality(const trace_t *trace, spatial_locality_t *result)
{
    result->same_line_transitions = 0;
    result->total_transitions = 0;
    result->score = 0.0;

    if (trace->count < 2)
    {
        return;
    }

    for (int i = 0; i < trace->count - 1; i++)
    {
        uint64_t current_line = trace->entries[i].address / CACHE_LINE_SIZE;
        uint64_t next_line = trace->entries[i + 1].address / CACHE_LINE_SIZE;
        result->total_transitions++;
        if (current_line == next_line)
        {
            result->same_line_transitions++;
        }
    }

    result->score = (100.0 * result->same_line_transitions) / result->total_transitions;
}

void print_spatial_locality(const spatial_locality_t *result)
{
    printf("\nSpatial Locality Analysis\n");
    printf("====================================\n\n");
    printf("Total Transitions     : %llu\n", (unsigned long long) result->total_transitions);
    printf("Same-Line Transitions : %llu\n", (unsigned long long) result->same_line_transitions);
	printf("Spatial Locality      : %.2f%%\n", result->score);
    printf("\nClassification       : ");
    if (result->score >= 80.0)
    {
        printf("Str*ng\n");
    }
    else if (result->score >= 50.0)
    {
        printf("Moderate\n");
    }
    else
	{
        printf("Poor\n");
    }
    printf("\n");
}