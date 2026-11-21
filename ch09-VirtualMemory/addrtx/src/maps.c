#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "addrtx.h"

static int global_var = 42;

int find_region(uint64_t address, memory_region_t *region)
{
	FILE *fp = fopen("/proc/self/maps", "r");

	if(fp == NULL)
		return 0;

	char line[512];

	while(fgets(line, sizeof(line), fp))
	{
		unsigned long start;
		unsigned long end;

		char perms[8] = {0};
		char path[256] = "";

		int fields = sscanf(line, "%lx-%lx %7s %*s %*s %*s %255[^\n]", &start, &end, perms, path);

		if(address >= start && address < end)
		{
			region->start = start;
			region->end = end;

			strcpy(region->permissions, perms);
			
			if(fields == 4)
			{
				strcpy(region->pathname, path);
			}
			else
			{
				region->pathname[0] = '\0';
			}
					
			fclose(fp);

			return 1;
		}

	}

	fclose(fp);

	return 0;
}

void print_region(uint64_t address)
{
	memory_region_t region;

	printf("\nProcess Memory Region\n");
	printf("Address : 0x%lx\n\n", address);
	if(!find_region(address, &region))
	{
		printf("Region not found.\n\n");
		return;
	}

	printf("Region start	: 0x%lx\n", region.start);
	printf("Region end	: 0x%lx\n", region.end);
	printf("Permissions	: %s\n", region.permissions);
	printf("Mapping		: %s\n", region.pathname[0] ? region.pathname : "[anonymous]");

	printf("\n");
}

void print_self_regions()
{
	int stack_var = 10;
	int *heap_var = malloc(sizeof(int));

	printf("\nAddrTx Self Inspection\n");
	printf("=========================================\n");
	printf("Global variable\n");
	print_region((uint64_t)&global_var);
	printf("Heap Object\n");
	print_region((uint64_t)heap_var);
	printf("Stack Variable\n");
	print_region((uint64_t)&stack_var);
	free(heap_var);
}
