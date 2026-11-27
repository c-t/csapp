#include "memviz.h"

void analyze_address(uint64_t address, address_info_t *info)
{
    info->address = address;
    info->page_number = address / PAGE_SIZE;
    info->page_offset = address % PAGE_SIZE;
    info->cache_line = address / CACHE_LINE_SIZE;
    info->cache_offset = address % CACHE_LINE_SIZE;
}