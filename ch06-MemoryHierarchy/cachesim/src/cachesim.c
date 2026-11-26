#include <stdio.h>
#include <stdlib.h>

#include "cachesim.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <hex-address>\n", argv[0]);
        return 1;
    }

    uint32_t address = (uint32_t)strtoul(argv[1], NULL, 0);
    cache_address_t decoded;
    decode_address( address, &decoded);
    print_address_info( &decoded);

	cache_t cache;
	initialize_cache(&cache);
	print_cache(&cache);

    return 0;
}