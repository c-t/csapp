#include <stdio.h>

#include "tlbsim.h"

int main(void)
{
    tlb_t tlb;

    initialize_tlb(&tlb);
    populate_tlb_entry(&tlb, 0, 0x7ffff84e3, 0x10e3);
    populate_tlb_entry(&tlb, 1, 0x58dc74280, 0x1080);
    print_tlb(&tlb);

    return 0;
}