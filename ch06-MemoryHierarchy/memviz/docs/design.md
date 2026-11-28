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
Address Analyzer
    |
    +--> Histograms
    |
    +--> Spatial Locality

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