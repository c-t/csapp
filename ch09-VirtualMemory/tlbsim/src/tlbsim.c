#include <stdint.h>
#include <stdio.h>

#include "tlbsim.h"

int main(void)
{
    tlb_t tlb;
    initialize_tlb(&tlb);
    populate_tlb_entry(&tlb, 0, 0x7ffff84e3, 0x10e3);
    populate_tlb_entry(&tlb, 1, 0x58dc74280, 0x1080);
    print_tlb(&tlb);

    uint64_t frame;
    int hit = tlb_lookup(&tlb, 0x7ffff84e3, &frame);
    print_lookup_result(0x7ffff84e3, hit, frame);
	
	uint64_t miss_vpn = 0x12345678;
	hit = tlb_lookup(&tlb, miss_vpn, &frame);
	print_lookup_result(miss_vpn, hit, frame);
	
	if (!hit)
	{
		frame = simulate_page_walk(miss_vpn);
		print_fill_result(miss_vpn, frame);
		insert_translation(&tlb, miss_vpn, frame);
	}

	hit = tlb_lookup(&tlb, miss_vpn, &frame);
	print_lookup_result(miss_vpn, hit, frame);
	print_tlb(&tlb);
	run_access_pattern(&tlb);

	tlb_t fifo_tlb;
	initialize_tlb(&fifo_tlb);
	run_fifo_demo(&fifo_tlb);

    return 0;
}