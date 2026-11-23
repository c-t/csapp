#include "ptsim.h"

void generate_physical_address(uint64_t frame, uint16_t offset, translation_result_t *result)
{
    result->frame = frame;
    result->physical_address = (frame << 12) | offset;
}