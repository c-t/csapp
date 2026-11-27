#ifndef MEMVIZ_H
#define MEMVIZ_H

#include <stdint.h>

#define MAX_TRACE_ENTRIES	1024
#define PAGE_SIZE        	4096
#define CACHE_LINE_SIZE    	64

typedef struct
{
    uint64_t address;
} trace_entry_t;

typedef struct
{
    trace_entry_t entries[MAX_TRACE_ENTRIES];
    int count;
} trace_t;

typedef struct
{
    uint64_t address;
    uint64_t page_number;
    uint64_t page_offset;
    uint64_t cache_line;
    uint64_t cache_offset;
} address_info_t;

int load_trace(const char *filename, trace_t *trace);
void print_trace(const trace_t *trace);
void analyze_address(uint64_t address, address_info_t *info);
void print_analysis(const trace_t *trace);

#endif