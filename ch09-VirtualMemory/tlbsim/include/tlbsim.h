#ifndef TLBSIM_H
#define TLBSIM_H

#include <stdint.h>

#define TLB_ENTRIES 16
#define SIM_TLB_SIZE 4

typedef struct
{
    uint64_t vpn;
    uint64_t frame;
    int valid;
	uint64_t last_used;
} tlb_entry_t;

typedef struct
{
    tlb_entry_t entries[TLB_ENTRIES];
	int next_victim;
	uint64_t access_counter;
} tlb_t;

void initialize_tlb(tlb_t *tlb);
void populate_tlb_entry(tlb_t *tlb, int index, uint64_t vpn, uint64_t frame);
void print_tlb(const tlb_t *tlb);
int tlb_lookup(tlb_t *tlb, uint64_t vpn, uint64_t *frame);
void print_lookup_result(uint64_t vpn, int hit, uint64_t frame);
uint64_t simulate_page_walk(uint64_t vpn);
int insert_translation(tlb_t *tlb, uint64_t vpn, uint64_t frame);
void print_fill_result(uint64_t vpn, uint64_t frame);
void run_access_pattern(tlb_t *tlb);
void fifo_insert(tlb_t *tlb, uint64_t vpn, uint64_t frame);
void run_fifo_demo(tlb_t *tlb);
void lru_insert(tlb_t *tlb, uint64_t vpn, uint64_t frame);
void run_lru_demo(tlb_t *tlb);

#endif