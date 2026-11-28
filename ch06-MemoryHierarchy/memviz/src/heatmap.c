#include <stdio.h>

#include "memviz.h"

static void histogram_increment(histogram_t *histogram, uint64_t key)
{
    for (int i = 0; i < histogram->count; i++)
    {
        if (histogram->entries[i].key == key)
        {
            histogram->entries[i].count++;
            return;
        }
    }

    histogram->entries[histogram->count].key = key;
    histogram->entries[histogram->count].count = 1;
    histogram->count++;
}

void build_page_histogram(const trace_t *trace, histogram_t *histogram)
{
    histogram->count = 0;

    for (int i = 0; i < trace->count; i++)
    {
        uint64_t page = trace->entries[i].address / PAGE_SIZE;
        histogram_increment(histogram, page);
    }
}

void build_cacheline_histogram(const trace_t *trace, histogram_t *histogram)
{
    histogram->count = 0;

    for (int i = 0; i < trace->count; i++)
    {
        uint64_t line = trace->entries[i].address / CACHE_LINE_SIZE;
        histogram_increment(histogram, line);
    }
}

void print_page_histogram(const histogram_t *histogram)
{
    printf("\nPage Histogram\n");
    printf("====================================\n\n");
    printf("%-10s %-10s\n", "Page", "Accesses");
    printf("----------------------\n");

    for (int i = 0; i < histogram->count; i++)
    {
        printf("%-10llu %-10llu\n", (unsigned long long) histogram->entries[i].key, (unsigned long long) histogram->entries[i].count);
    }

    printf("\n");
}

void print_cacheline_histogram( const histogram_t *histogram)
{
    printf("\nCache Line Histogram\n");
    printf("====================================\n\n");
    printf("%-10s %-10s\n", "Line", "Accesses");
    printf("----------------------\n");

    for (int i = 0; i < histogram->count; i++)
    {
        printf("%-10llu %-10llu\n", (unsigned long long) histogram->entries[i].key, (unsigned long long) histogram->entries[i].count);
    }

    printf("\n");
}

static void print_bar(uint64_t count)
{
    for (uint64_t i = 0; i < count; i++)
    {
        printf("*");
    }
}

void print_page_heatmap(const histogram_t *histogram)
{
    printf("\nPage Heat Map\n");
    printf("====================================\n\n");

    for (int i = 0; i < histogram->count; i++)
    {
        printf("Page %-6llu ", (unsigned long long) histogram->entries[i].key);
        print_bar(histogram->entries[i].count);
        printf(" (%llu)\n", (unsigned long long) histogram->entries[i].count);
    }

    printf("\n");
}

void print_cacheline_heatmap(const histogram_t *histogram)
{
    printf("\nCache Line Heat Map\n");
    printf("====================================\n\n");

    for (int i = 0; i < histogram->count; i++)
    {
        printf("Line %-6llu ", (unsigned long long) histogram->entries[i].key);
        print_bar(histogram->entries[i].count);
        printf(" (%llu)\n", (unsigned long long) histogram->entries[i].count);
    }

    printf("\n");
}