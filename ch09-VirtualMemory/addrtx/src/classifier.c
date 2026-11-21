#include "addrtx.h"

region_type_t classify_address(uint64_t address)
{
	//Typical linux x86-64 userspace layout
	if(address >= 0x700000000000ULL)
		return REGION_STACK;

	if(address >= 0x500000000000ULL)
		return REGION_HEAP_DATA;

	return REGION_UNKNOWN;
}

const char* region_name(region_type_t region)
{
	switch(region)
	{
		case REGION_STACK:
			return "STACK";
		case REGION_HEAP_DATA:
			return "HEAP_DATA";
		default:
			return "UNKNOWN";
	}
}
