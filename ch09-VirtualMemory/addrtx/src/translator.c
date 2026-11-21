#include "addrtx.h"

void translate_address(uint64_t address, address_info_t *info)
{
	info->virtual_address = address;
	info->vpn = address >> 12;
	info->offset = address & PAGE_OFFSET_MASK;
}
