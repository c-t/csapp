#include <assert.h>

#include "memviz.h"

int main(void)
{
    trace_t trace;

    uint64_t sequential[] = {
        UINT64_C(0x1000), UINT64_C(0x1004),
        UINT64_C(0x1008), UINT64_C(0x100c)
    };

    trace.count = 4;
    for (int i = 0; i < trace.count; i++)
        trace.entries[i].address = sequential[i];

    spatial_locality_t spatial;
    analyze_spatial_locality(&trace, &spatial);
    assert(spatial.total_transitions == 3);
    assert(spatial.same_line_transitions == 3);
    assert(spatial.score == 100.0);

    temporal_locality_t temporal;
    analyze_temporal_locality(&trace, &temporal);
    assert(temporal.unique_accesses == 4);
    assert(temporal.reused_accesses == 0);
    assert(temporal.average_reuse_distance == 0.0);

    trace.count = 6;
    uint64_t reused[] = {
        UINT64_C(0x1000), UINT64_C(0x2000),
        UINT64_C(0x1000), UINT64_C(0x1000),
        UINT64_C(0x2000), UINT64_C(0x1000)
    };
    for (int i = 0; i < trace.count; i++)
        trace.entries[i].address = reused[i];

    analyze_temporal_locality(&trace, &temporal);
    assert(temporal.unique_accesses == 2);
    assert(temporal.reused_accesses == 4);
    assert(temporal.average_reuse_distance > 0.0);

    return 0;
}
