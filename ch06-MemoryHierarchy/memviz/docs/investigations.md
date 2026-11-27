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