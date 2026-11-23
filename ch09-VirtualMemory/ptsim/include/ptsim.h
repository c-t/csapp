#ifndef PTSIM_H
#define PTSIM_H

#include <stdint.h>

#define PT_ENTRIES 512
#define MAX_ADDRESSES 16

typedef struct
{
    uint64_t virtual_address;
    uint16_t pml4;
    uint16_t pdpt;
    uint16_t pd;
    uint16_t pt;
    uint16_t offset;
} page_indices_t;

typedef struct
{
    uint64_t frame;
    int present;
} pt_entry_t;

typedef struct
{
    pt_entry_t entries[PT_ENTRIES];
} page_table_t;

typedef struct
{
    page_table_t pml4;
    page_table_t pdpt;
    page_table_t pd;
    page_table_t pt;
} page_walk_t;

typedef struct
{
    uint64_t frame;
    uint64_t physical_address;
} translation_result_t;

typedef struct
{
    uint64_t virtual_address;
    uint64_t physical_address;
    uint64_t frame;
    uint16_t offset;
} translation_entry_t;

void extract_indices(uint64_t address, page_indices_t *indices);
void print_indices(const page_indices_t *indices);
void print_visualization(const page_indices_t *indices);
void initialize_page_table(page_table_t *table);
void populate_entry(page_table_t *table, uint16_t index, uint64_t frame);
void print_page_table_entry(const page_table_t *table, uint16_t index);
void print_page_table_structure(const page_indices_t *idx);
void initialize_page_walk(page_walk_t *walk, const page_indices_t *idx);
int perform_page_walk(const page_walk_t *walk, const page_indices_t *idx, uint64_t *frame);
void print_page_walk(const page_walk_t *walk, const page_indices_t *idx);
void generate_physical_address(uint64_t frame, uint16_t offset, translation_result_t *result);
void print_physical_address(const translation_result_t *result, uint16_t offset);
uint64_t get_frame(const page_walk_t *walk, const page_indices_t *idx);
void run_multi_translation(void);

#endif