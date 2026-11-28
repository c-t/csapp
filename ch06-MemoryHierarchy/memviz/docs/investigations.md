# MemViz Investigation

## What is MemViz?

MemViz (Memory Visualizer) is a tool that analyzes memory access traces and
displays access behavior in a human-readable form.

The goal is not to simulate hardware.

The goal is to help developers understand:

- Memory access patterns
- Spatial locality
- Temporal locality
- Page usage
- Cache-line usage
- Hot memory regions

---

## Why Memory Visualization Matters

Modern CPUs depend heavily on cache efficiency.

Two programs can perform the same computation but have vastly different
performance depending on memory access behavior.

Visualization helps identify:

- Sequential access patterns
- Random access patterns
- Strided access patterns
- Frequently reused regions

---

## Locality

### Spatial Locality

If an address is accessed, nearby addresses are likely to be accessed soon.

Example:

0x1000
0x1004
0x1008
0x100C

This benefits cache lines.

---

### Temporal Locality

If an address is accessed, it is likely to be accessed again.

Example:

A
B
A

The second access to A may hit in cache.

---

## Memory Granularity

### Byte

Smallest addressable unit.

### Cache Line

Typically 64 bytes.

Addresses sharing the same cache line:

0x1000
0x1008
0x1010

may be served from a single cache fill.

### Page

Typically 4096 bytes.

Addresses:

0x1000
0x1800
0x1F00

belong to the same page.

---

## Common Access Patterns

### Sequential

0
64
128
192
256

Excellent locality.

---

### Strided

0
256
512
768

Moderate locality.

---

### Random

15
9000
123
45000

Poor locality.

---

### Looping

A
B
C
A
B
C

Strong temporal locality.

---

## Existing Visualization Concepts

Many performance tools provide:

- Histograms
- Heat maps
- Address distributions
- Reuse-distance graphs
- Access frequency summaries

MemViz will implement simplified versions suitable for learning.

## Phase 1 Findings

A memory trace is simply an ordered sequence of memory accesses.

Example:

0x1000
0x1004
0x1008
0x2000

The parser serves as the foundation for all future analyses.

Future phases will derive:

- Page numbers
- Cache-line numbers
- Access frequencies
- Locality metrics

from these raw addresses.

## Phase 2 Findings

Address analysis reveals hidden structure within a memory trace.

Multiple addresses may belong to:

- The same cache line
- The same page

These relationships are important because they directly influence cache and TLB behavior.

Example:

0x1000
0x1004
0x1008
0x100c

All belong to:

Page 1
Cache Line 64

This demonstrates spatial locality.

## Phase 3 Findings

Frequency histograms reveal memory hotspots.

Example:

Page 1 -> 6 accesses
Page 2 -> 2 accesses

Line 64 -> 6 accesses
Line 128 -> 2 accesses

Hotspots indicate regions that may benefit from
cache residency and exhibit locality.

## Phase 4 Findings

Spatial locality measures how frequently nearby
memory locations are accessed together.

Strong spatial locality improves cache efficiency
because a single cache-line fetch can satisfy
multiple accesses.

Example Trace:

0x1000
0x1004
0x1008
0x100c

All belong to the same cache line and therefore
demonstrate strong spatial locality.

Observed Result:

Spatial Locality = 71.43%

Classification = Moderate

## Phase 5 Findings

Temporal locality measures whether
memory locations are reused over time.

Example:

A
B
C
A

The second access to A exhibits temporal
locality.

Good temporal locality improves cache
effectiveness because data remains useful
after it is loaded.

Observed Results:

Unique Accesses : 6
Reused Accesses : 2

Temporal Locality : 25%

Classification : Moderate

## Phase 6 Findings

Heat maps provide a visual representation of memory activity.

Advantages:

- Quickly identify hot regions
- Easier to interpret than raw counts
- Useful for spotting memory hotspots

Example:

Page 1      ****** (6)
Page 2      **     (2)

The longer bar immediately identifies the hottest page.