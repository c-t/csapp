# MemViz Notes

## Learning Goals

- Understand memory traces
- Understand spatial locality
- Understand temporal locality
- Understand page-level behavior
- Understand cache-line behavior
- Visualize memory accesses

## Relationship To Previous Projects

PTSim
    |
    v
TLBSim
    |
    v
CacheSim
    |
    v
MemViz

MemViz provides a visual perspective on the memory behavior modeled by the
previous simulators.

## Future Extensions

- CSV export
- Trace replay
- Interactive console views
- CacheSim integration
- TLBSim integration
- Graphical heat maps

## Development Progress

### Phase 0 Completed

- Project investigation completed
- Architecture defined
- Roadmap established
- Sample trace created

### Phase 1 Completed

Implemented:

- Trace entry structure
- Trace container
- File parser
- Address loader
- Trace visualization
- Access counter

Example Output:

Memory Trace
====================================

Index    Address
------------------------------------
0        0x0000000000001000
1        0x0000000000001004
...

Total Accesses : 8

### Phase 2 Completed

Implemented:

- Address analysis module
- Page-number extraction
- Page-offset extraction
- Cache-line computation
- Cache-line offset computation

Example:

Address            Page   Line
--------------------------------
0x1000             1      64
0x1004             1      64
0x1008             1      64

Observation:

Several accesses share the same cache line and page,
illustrating spatial locality.

### Phase 3 Completed

Implemented:

- Histogram data structures
- Page-frequency analysis
- Cache-line-frequency analysis
- Histogram visualization

Results:

Page 1 -> 6 accesses
Page 2 -> 2 accesses

Line 64 -> 6 accesses
Line 128 -> 2 accesses

Observation:

The majority of accesses are concentrated
within a single page and cache line,
suggesting strong spatial locality.

### Phase 4 Completed

Implemented:

- Spatial locality analysis
- Cache-line transition tracking
- Locality scoring
- Locality classification

Sample Results:

Total Transitions     : 7
Same-Line Transitions : 5

Spatial Locality      : 71.43%

Classification        : Moderate

Observation:

Most accesses occur within a small number of
cache lines, indicating good spatial locality.

### Phase 5 Completed

Implemented:

- Reuse detection
- Reuse distance calculation
- Temporal locality scoring
- Temporal locality classification

Results:

Unique Accesses         : 6
Reused Accesses         : 2

Average Reuse Distance  : 6

Temporal Locality       : 25%

Classification          : Moderate

Observation:

The trace contains repeated accesses to
0x1000 and 0x1004, demonstrating temporal
locality and memory reuse.

### Phase 6 Completed

Implemented:

- Page heat map visualization
- Cache-line heat map visualization

Results:

Page Heat Map

Page 1      ****** (6)
Page 2      **     (2)

Cache Line Heat Map

Line 64     ****** (6)
Line 128    **     (2)

Observation:

A small number of pages and cache lines dominate the trace.
This confirms the hotspot behavior previously seen in histogram analysis.