# MemViz

MemViz (Memory Visualizer) is an educational tool that analyzes memory access
traces and visualizes memory behavior.

The goal is to understand:

- Memory access patterns
- Spatial locality
- Temporal locality
- Page usage
- Cache-line usage
- Hot memory regions

MemViz complements:

- PTSim
- TLBSim
- CacheSim

and helps connect low-level memory accesses to observed performance.

## Planned Features

- Trace file parsing
- Address analysis
- Page statistics
- Cache-line statistics
- Access histograms
- Spatial locality analysis
- Temporal locality analysis
- Heat maps
- Pattern classification

## Project Phases

- [x] Phase 0 - Investigation
- [x] Phase 1 - Trace Parser
- [x] Phase 2 - Address Analysis
- [ ] Phase 3 - Histograms
- [ ] Phase 4 - Spatial Locality
- [ ] Phase 5 - Temporal Locality
- [ ] Phase 6 - Heat Maps
- [ ] Phase 7 - Pattern Classification
- [ ] Phase 8 - MemViz v1.0

## Current Features

### Phase 1

- Load memory traces from file
- Parse hexadecimal addresses
- Store trace entries
- Display loaded trace contents
- Report total memory accesses

### Phase 2

MemViz now derives:

- Page Number
- Page Offset
- Cache Line Number
- Cache Line Offset

for every memory access.