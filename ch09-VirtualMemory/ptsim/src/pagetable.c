#include <stdio.h>

#include "ptsim.h"

void initialize_page_table(page_table_t *table)
{
    for (int i = 0; i < PT_ENTRIES; i++)
    {
        table->entries[i].present = 0;
        table->entries[i].frame = 0;
    }
}

void populate_entry(page_table_t *table, uint16_t index, uint64_t frame)
{
    table->entries[index].present = 1;
    table->entries[index].frame = frame;
}

void print_page_table_entry(const page_table_t *table, uint16_t index)
{
    printf("Index %u\n", index);
    printf("Present : %s\n", table->entries[index].present ? "yes" : "no");
    printf("Frame   : 0x%lx\n\n", table->entries[index].frame);
}