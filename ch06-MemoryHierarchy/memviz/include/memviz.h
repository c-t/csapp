#ifndef MEMVIZ_H
#define MEMVIZ_H

#include <stdint.h>

#define MAX_TRACE_ENTRIES 1024

typedef struct
{
    uint64_t address;
} trace_entry_t;

typedef struct
{
    trace_entry_t entries[MAX_TRACE_ENTRIES];
    int count;
} trace_t;

int load_trace(const char *filename, trace_t *trace);
void print_trace(const trace_t *trace);

#endif