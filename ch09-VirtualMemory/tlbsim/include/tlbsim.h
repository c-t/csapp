#ifndef TLBSIM_H
#define TLBSIM_H

#include <stdint.h>

#define TLB_ENTRIES 16

typedef struct
{
    uint64_t vpn;
    uint64_t frame;
    int valid;
} tlb_entry_t;

typedef struct
{
    tlb_entry_t entries[TLB_ENTRIES];
} tlb_t;

void initialize_tlb(tlb_t *tlb);
void populate_tlb_entry(tlb_t *tlb, int index, uint64_t vpn, uint64_t frame);
void print_tlb(const tlb_t *tlb);
int tlb_lookup(const tlb_t *tlb, uint64_t vpn, uint64_t *frame);
void print_lookup_result(uint64_t vpn, int hit, uint64_t frame);

#endif