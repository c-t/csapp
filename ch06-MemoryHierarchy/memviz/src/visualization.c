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