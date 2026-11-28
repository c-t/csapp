#include <assert.h>

#include "memviz.h"

static trace_t make_trace(const uint64_t *addresses, int count)
{
    trace_t trace;
    trace.count = count;

    for (int i = 0; i < count; i++)
        trace.entries[i].address = addresses[i];

    return trace;
}

int main(void)
{
    pattern_analysis_t result;

    uint64_t sequential[] = {
        UINT64_C(0x1000), UINT64_C(0x1004),
        UINT64_C(0x1008), UINT64_C(0x100c)
    };
    trace_t trace = make_trace(sequential, 4);
    analyze_pattern(&trace, &result);
    assert(result.type == PATTERN_SEQUENTIAL);
    assert(result.stride == 4);

    uint64_t strided[] = {
        UINT64_C(0x1000), UINT64_C(0x1080),
        UINT64_C(0x1100), UINT64_C(0x1180)
    };
    trace = make_trace(strided, 4);
    analyze_pattern(&trace, &result);
    assert(result.type == PATTERN_STRIDED);
    assert(result.stride == 128);

    uint64_t looping[] = {
        UINT64_C(0x1000), UINT64_C(0x1004),
        UINT64_C(0x1000), UINT64_C(0x1004)
    };
    trace = make_trace(looping, 4);
    analyze_pattern(&trace, &result);
    assert(result.type == PATTERN_LOOPING);

    uint64_t random[] = {
        UINT64_C(0x1000), UINT64_C(0x3000),
        UINT64_C(0x2000), UINT64_C(0x5000)
    };
    trace = make_trace(random, 4);
    analyze_pattern(&trace, &result);
    assert(result.type == PATTERN_RANDOM);

    histogram_t page_histogram;
    build_page_histogram(&trace, &page_histogram);
    assert(page_histogram.count == 4);

    histogram_t cacheline_histogram;
    build_cacheline_histogram(&trace, &cacheline_histogram);
    assert(cacheline_histogram.count == 4);

    return 0;
}
