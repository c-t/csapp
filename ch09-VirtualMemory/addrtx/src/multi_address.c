#include <stdio.h>
#include <stdint.h>

#include "addrtx.h"

void analyze_addresses(uint64_t* addresses, size_t count)
{
	address_entry_t entries[32];

	if(count > 32)
		count = 32;

	printf("\nMulti-address Analysis\n");
	printf("=====================================\n\n");
	printf("%-18s %-15s\n", "Address", "VPN");
	printf("-------------------------------------\n\n");
	for(size_t i = 0; i < count; i++)
	{
		entries[i].address = addresses[i];
		entries[i].vpn = addresses[i] >> 12;
		printf("0x%-16lx 0x%lx\n", entries[i].address, entries[i].vpn);
	}

	printf("\nShared Page Analysis\n");
	printf("=====================================\n\n");

	int found = 0;
	for(size_t i = 0; i < count; i++)
	{
		for(size_t j = i + 1; j < count; j++)
		{
			if(entries[i].vpn == entries[j].vpn)
			{
				found = 1;
				printf("Shared VPN: 0x%lx\n", entries[i].vpn);
				printf("   0x%lx\n", entries[i].address);
				printf("   0x%lx\n", entries[j].address);
				printf("Relationship: Same 4 KB Page\n\n");
		
			}
		}
	}

	if(!found)
	{
		printf("No addresses share a page.\n\n");
	}
}
