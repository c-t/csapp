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