#include <stdio.h>

#include "memviz.h"

void print_trace(const trace_t *trace)
{
    printf("\nMemory Trace\n");
    printf("====================================\n\n");
    printf("%-8s %-18s\n", "Index", "Address");
    printf("------------------------------------\n");

    for (int i = 0; i < trace->count; i++)
    {
        printf("%-8d 0x%016llx\n", i, (unsigned long long) trace->entries[i].address);
    }

    printf("\nTotal Accesses : %d\n\n", trace->count);
}

void print_analysis(const trace_t *trace)
{
    printf("\nAddress Analysis\n");
    printf("===============================================================\n\n");
    printf("%-18s %-8s %-10s %-10s %-10s\n", "Address", "Page", "PageOff", "Line", "LineOff");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < trace->count; i++)
    {
        address_info_t info;
        analyze_address(trace->entries[i].address, &info);
        printf("0x%016llx %-8llu %-10llu %-10llu %-10llu\n", (unsigned long long)info.address, (unsigned long long)info.page_number, 
			(unsigned long long)info.page_offset, (unsigned long long)info.cache_line, (unsigned long long)info.cache_offset);
    }

    printf("\n");
}

void build_summary(const trace_t *trace, const histogram_t *page_histogram, const histogram_t *cacheline_histogram, summary_t *summary)
{
    summary->total_accesses = trace->count;
    summary->hottest_page = 0;
    summary->hottest_page_accesses = 0;
    summary->hottest_cacheline = 0;
    summary->hottest_cacheline_accesses = 0;

    for (int i = 0; i < page_histogram->count; i++)
    {
        if (page_histogram->entries[i].count > summary->hottest_page_accesses)
        {
            summary->hottest_page =  page_histogram->entries[i].key;
            summary->hottest_page_accesses = page_histogram->entries[i].count;
        }
    }

    for (int i = 0; i < cacheline_histogram->count; i++)
    {
        if (cacheline_histogram->entries[i].count > summary->hottest_cacheline_accesses)
        {
            summary->hottest_cacheline = cacheline_histogram->entries[i].key;
            summary->hottest_cacheline_accesses = cacheline_histogram->entries[i].count;
        }
    }
}

void print_summary(const summary_t *summary, const spatial_locality_t *spatial, const temporal_locality_t *temporal, const pattern_analysis_t *pattern)
{
    printf("\nMemory Trace Summary\n");
    printf("================================================\n\n");
    printf("Total Accesses       : %llu\n", (unsigned long long) summary->total_accesses);
    printf("Hottest Page         : %llu (%llu accesses)\n", (unsigned long long) summary->hottest_page, (unsigned long long) summary->hottest_page_accesses);
    printf("Hottest Cache Line   : %llu (%llu accesses)\n", (unsigned long long) summary->hottest_cacheline, (unsigned long long) summary->hottest_cacheline_accesses);
    printf("Spatial Locality     : %.2f%%\n", spatial->score);
    printf("Temporal Locality    : %.2f%%\n", temporal->score);
    printf("Access Pattern       : ");
	
    switch (pattern->type)
    {
        case PATTERN_SEQUENTIAL:
            printf("Sequential");
            break;
        case PATTERN_STRIDED:
            printf("Strided");
            break;
        case PATTERN_LOOPING:
            printf("Looping");
            break;
        case PATTERN_RANDOM:
            printf("Random");
            break;
        default:
            printf("Unknown");
            break;
    }

    printf("\n");
    printf("Overall Assessment   : ");
    if (spatial->score >= 70.0 && temporal->score >= 20.0)
    {
        printf("Cache-Friendly\n");
    }
    else
    {
        printf("Cache-Unfriendly\n");
    }
}