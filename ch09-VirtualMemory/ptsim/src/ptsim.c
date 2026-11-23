#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ptsim.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <address>\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint64_t address = strtoull(argv[1], NULL, 0);

    page_indices_t indices;
    extract_indices(address, &indices);
    print_indices(&indices);
	print_visualization(&indices);
	print_page_table_structure(&indices);
	
	page_table_t pt;
	initialize_page_table(&pt);
	populate_entry(&pt, indices.pt, 0x12345);	
	print_page_table_entry(&pt, indices.pt);
	
	page_walk_t walk;
	initialize_page_walk(&walk, &indices);
	print_page_walk(&walk, &indices);	

	translation_result_t result;
	uint64_t frame = get_frame(&walk, &indices);
	generate_physical_address(frame, indices.offset, &result);
	print_physical_address(&result, indices.offset);

    return EXIT_SUCCESS;
}