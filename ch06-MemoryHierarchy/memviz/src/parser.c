#include <stdio.h>
#include <stdlib.h>

#include "memviz.h"

int load_trace(const char *filename, trace_t *trace)
{
    FILE *fp;
    char line[128];

    trace->count = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("fopen");
        return -1;
    }

    while (fgets(line, sizeof(line), fp))
    {
        if (trace->count >= MAX_TRACE_ENTRIES)
        {
            printf("Trace limit reached\n");
            break;
        }

        trace->entries[trace->count].address = strtoull(line, NULL, 0);
        trace->count++;
    }

    fclose(fp);

    return trace->count;
}