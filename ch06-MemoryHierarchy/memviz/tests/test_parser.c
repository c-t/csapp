#include <assert.h>
#include <stdint.h>

#include "memviz.h"

int main(void)
{
    trace_t trace;

    assert(load_trace("samples/sample_trace.txt", &trace) == 8);
    assert(trace.count == 8);
    assert(trace.entries[0].address == UINT64_C(0x1000));
    assert(trace.entries[7].address == UINT64_C(0x1004));

    address_info_t info;
    analyze_address(UINT64_C(0x1234), &info);
    assert(info.address == UINT64_C(0x1234));
    assert(info.page_number == UINT64_C(0x1));
    assert(info.page_offset == UINT64_C(0x234));
    assert(info.cache_line == UINT64_C(0x48));
    assert(info.cache_offset == UINT64_C(0x34));

    histogram_t pages;
    build_page_histogram(&trace, &pages);
    assert(pages.count == 2);

    histogram_t cachelines;
    build_cacheline_histogram(&trace, &cachelines);
    assert(cachelines.count == 2);

    return 0;
}
