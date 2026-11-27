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