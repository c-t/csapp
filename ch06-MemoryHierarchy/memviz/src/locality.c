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

void analyze_temporal_locality(const trace_t *trace, temporal_locality_t *result)
{
    result->reused_accesses = 0;
    result->unique_accesses = 0;
    result->total_reuse_distance = 0;
    result->average_reuse_distance = 0.0;
    result->score = 0.0;

    for (int i = 0; i < trace->count; i++)
    {
        int found = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            if (trace->entries[i].address == trace->entries[j].address)
            {
                result->reused_accesses++;
                result->total_reuse_distance += (i - j);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            result->unique_accesses++;
        }
    }

    if (result->reused_accesses > 0)
    {
        result->average_reuse_distance = (double) result->total_reuse_distance / result->reused_accesses;
    }

    result->score = (100.0 * result->reused_accesses) / trace->count;
}

void print_temporal_locality(
    const temporal_locality_t *result)
{
    printf("\nTemporal Locality Analysis\n");
    printf("====================================\n\n");
    printf("Unique Accesses         : %llu\n", (unsigned long long) result->unique_accesses);
    printf("Reused Accesses         : %llu\n", (unsigned long long) result->reused_accesses);
    printf("Average Reuse Distance  : %.2f\n", result->average_reuse_distance);
    printf("Temporal Locality       : %.2f%%\n", result->score);
    printf("\nClassification          : ");

    if (result->score >= 50.0)
    {
        printf("Strong\n");
    }
    else if (result->score >= 20.0)
    {
        printf("Moderate\n");
    }
    else
    {
        printf("Poor\n");
    }

    printf("\n");
}

void analyze_pattern(const trace_t *trace, pattern_analysis_t *result)
{
    result->type = PATTERN_UNKNOWN;
    result->stride = 0;

    if (trace->count < 2)
    {
        return;
    }

    /* Check for looping pattern */
    for (int i = 1; i < trace->count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (trace->entries[i].address == trace->entries[j].address)
            {
                result->type = PATTERN_LOOPING;
                return;
            }
        }
    }

    int64_t stride = (int64_t)trace->entries[1].address - (int64_t)trace->entries[0].address;

    int same_stride = 1;

    for (int i = 2; i < trace->count; i++)
    {
        int64_t current_stride = (int64_t)trace->entries[i].address - (int64_t)trace->entries[i - 1].address;
        if (current_stride != stride)
        {
            same_stride = 0;
            break;
        }
    }

    if (same_stride)
    {
        result->stride = stride;
        if (stride == 4 ||stride == 8 || stride == 16 || stride == 32 || stride == 64)
        {
            result->type = PATTERN_SEQUENTIAL;
        }
        else
        {
            result->type = PATTERN_STRIDED;
        }
        return;
    }

    result->type = PATTERN_RANDOM;
}

void print_pattern_analysis(const pattern_analysis_t *result)
{
    printf("\nPattern Classification\n");
    printf("====================================\n\n");
    printf("Pattern : ");

    switch (result->type)
    {
        case PATTERN_SEQUENTIAL:
            printf("Sequential\n");
            break;
        case PATTERN_STRIDED:
            printf("Strided\n");
            printf("Stride  : %lld\n", (long long)result->stride);
            break;
        case PATTERN_LOOPING:
            printf("Looping\n");
            break;
        case PATTERN_RANDOM:
            printf("Random\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }

    printf("\n");
}