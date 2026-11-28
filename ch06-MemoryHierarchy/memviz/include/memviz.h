#ifndef MEMVIZ_H
#define MEMVIZ_H

#include <stdint.h>

#define MAX_TRACE_ENTRIES	1024
#define PAGE_SIZE        	4096
#define CACHE_LINE_SIZE    	64
#define MAX_HISTOGRAM_ENTRIES 1024

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

typedef struct
{
    uint64_t key;
    uint64_t count;
} histogram_entry_t;

typedef struct
{
    histogram_entry_t entries[MAX_HISTOGRAM_ENTRIES];
    int count;
} histogram_t;

typedef struct
{
    uint64_t same_line_transitions;
    uint64_t total_transitions;
    double score;
} spatial_locality_t;

typedef struct
{
    uint64_t reused_accesses;
    uint64_t unique_accesses;
    uint64_t total_reuse_distance;
    double score;
    double average_reuse_distance;
} temporal_locality_t;

int load_trace(const char *filename, trace_t *trace);
void print_trace(const trace_t *trace);
void analyze_address(uint64_t address, address_info_t *info);
void print_analysis(const trace_t *trace);
void build_page_histogram(const trace_t *trace, histogram_t *histogram);
void build_cacheline_histogram(const trace_t *trace, histogram_t *histogram);
void print_page_histogram(const histogram_t *histogram);
void print_cacheline_histogram(const histogram_t *histogram);
void analyze_spatial_locality( const trace_t *trace, spatial_locality_t *result);
void print_spatial_locality(const spatial_locality_t *result);
void analyze_temporal_locality(const trace_t *trace, temporal_locality_t *result);
void print_temporal_locality(const temporal_locality_t *result);
	
#endif