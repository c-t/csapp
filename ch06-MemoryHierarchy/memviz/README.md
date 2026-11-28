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

- [x] Phase 0 - Investigation
- [x] Phase 1 - Trace Parser
- [x] Phase 2 - Address Analysis
- [x] Phase 3 - Histograms
- [x] Phase 4 - Spatial Locality
- [x] Phase 5 - Temporal Locality
- [x] Phase 6 - Heat Maps
- [x] Phase 7 - Pattern Classification
- [x] Phase 8 - MemViz v1.0

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

### Phase 3

Implemented:

- Page access histograms
- Cache-line access histograms
- Hot-region identification

### Phase 4

Implemented:

- Cache-line transition analysis
- Spatial locality scoring
- Locality classification

### Phase 5

Implemented:

- Address reuse detection
- Reuse distance analysis
- Temporal locality scoring
- Temporal locality classification

### Phase 6

Implemented:

- Page heat maps
- Cache-line heat maps
- Hot-region visualization

### Phase 7

Implemented:

- Sequential pattern detection
- Strided pattern detection
- Looping pattern detection
- Random access detection

## Testing

Run all assert-based unit tests:

```sh
make test
```

Build the application and run the test suite:

```sh
make release
```

The tests cover:

- Trace loading and address decomposition
- Page and cache-line histograms
- Spatial and temporal locality
- Sequential, strided, looping, and random patterns

## Testing Support

Phase 7 functionality now has automated test coverage modeled after the CacheSim project:

- Three assert-based test executables
- `make test` for a test-only workflow
- `make release` for a clean application build followed by tests
- Strict warning and error checking with `-Werror`

## Phase 8 - MemViz v1.0

Phase 8 completes MemViz with a final trace summary containing:

- Total memory accesses
- Hottest page and access count
- Hottest cache line and access count
- Spatial locality score
- Temporal locality score
- Access-pattern classification
- Overall cache-friendliness assessment

The release also includes assert-based testing, strict warning checks, and
`make test` / `make release` workflows.

## Final Summary and Overall Assessment

MemViz v1.0 is now complete. The following milestones were achieved:

- Successful implementation of all planned features
- Extensive testing with assert-based unit tests
- Documentation updates and README completion

MemViz is now ready for use as a memory analysis and visualization tool.