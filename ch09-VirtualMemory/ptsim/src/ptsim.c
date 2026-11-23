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

    return EXIT_SUCCESS;
}