# MemViz Design

## Objective

Analyze memory traces and provide visual summaries of access behavior.

---

## Input

Text file containing memory addresses.

Example:

0x1000
0x1004
0x1008
0x2000

---

## Output

MemViz reports:

- Total accesses
- Unique addresses
- Unique pages
- Unique cache lines
- Spatial locality indicators
- Temporal locality indicators
- Access frequency statistics
- Heat maps

---

## Architecture

Trace File
    |
    v
Parser
    |
    v
Address Analysis
    |
    +--> Histograms
    |
    +--> Heat Maps
    |
    +--> Spatial Locality
    |
    +--> Temporal Locality
    |
    +--> Pattern Classification

---

## Planned Phases

Phase 1 Trace Parsing

Phase 2 Address Analysis

Phase 3 Histograms

Phase 4 Spatial Locality

Phase 5 Temporal Locality

Phase 6 Heat Maps

Phase 7 Pattern Classification

Phase 8 MemViz v1.0
	
## Implemented Features

### Phase 1 - Trace Parser

Input:

0x1000
0x1004
0x1008

Processing:

- Open trace file
- Parse hexadecimal addresses
- Store trace entries internally
- Count accesses

Output:

- Address listing
- Total access count

### Phase 2 - Address Analysis

Input:

Memory Address

Output:

- Page Number
- Page Offset
- Cache Line Number
- Cache Line Offset

Purpose:

Transform raw addresses into memory-system metadata that can be used for locality analysis and visualization.

### Phase 3 - Histograms

Input:

Address Analysis Data

Output:

- Page Frequency Histogram
- Cache-Line Frequency Histogram

Purpose:

Identify heavily accessed memory regions and prepare for locality analysis.

### Phase 4 - Spatial Locality

Input:

Cache-line sequence

Processing:

Compare consecutive accesses and determine
whether they reside in the same cache line.

Output:

- Same-line transition count
- Total transition count
- Spatial locality percentage
- Locality classification

Classifications:

Strong     >= 80%
Moderate   >= 50%
Poor       < 50%

### Phase 5 - Temporal Locality

Input:

Address sequence

Processing:

Track repeated accesses to previously
observed addresses.

Metrics:

- Unique accesses
- Reused accesses
- Average reuse distance
- Temporal locality score

Output:

Temporal locality percentage and
classification.

### Phase 6 - Heat Maps

Input:

Histogram data generated in Phase 3.

Processing:

Convert access frequencies into visual bars.

Output:

- Page heat map
- Cache-line heat map

Example:

Page 1      ****** (6)
Page 2      **     (2)

Line 64     ****** (6)
Line 128    **     (2)

## Phase 7 - Pattern Classification

Objective

Identify common memory-access patterns automatically.

Supported Patterns

### Sequential

Example:

0x1000
0x1004
0x1008
0x100C

Characteristics:

- Constant small stride
- Strong spatial locality
- Cache friendly

### Strided

Example:

0x1000
0x1100
0x1200
0x1300

Characteristics:

- Constant stride
- Moderate spatial locality

### Looping

Example:

A
B
C
A
B
C

Characteristics:

- Repeated address reuse
- Strong temporal locality

### Random

Example:

0x1000
0x9000
0x2300
0x50000

Characteristics:

- Weak locality
- Poor cache behavior