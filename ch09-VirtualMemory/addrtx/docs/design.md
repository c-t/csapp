# AddrTx Design

## Goal

Understand virtual address translation.

Learn:

- Virtual Addresses
- Page Numbers
- Page Offsets
- Address Translation
- Paging Fundamentals

---

## Roadmap

Phase 0 - Virtual Address Investigation ✅
Phase 1 - VPN + Offset Split ✅
Phase 2 - Binary Visualization ✅
Phase 3 - Address Classification
Phase 4 - Page Size Explorer
Phase 5 - Multi-Address Analysis
Phase 6 - Process Memory Regions
Phase 7 - Translation Statistics
Phase 8 - AddrTx v1.0

### Phase 0 - Virtual Address Investigation ✅ 

Investigated: 
- Global variables 
- Heap allocations 
- Stack variables Learning 

Objective: Understand the relationship between a virtual address and the process memory layout.

### Phase 1 - VPN + Offset Split ✅

Goal

Split a virtual address into:

```text
VPN
Offset
```

Implementation

```c
vpn = address >> 12;

offset = address & 0xFFF;
```

Learning Objective

Understand the fundamental structure of
virtual memory addresses before introducing
page tables and TLBs.

### Phase 2 - Binary Visualization ✅

Goal

Visualize the bit layout of a virtual address.

Implementation

Display:

```text
| VPN | OFFSET |
```

Learning Objective

Understand that hardware views a virtual
address as two fields:

- Virtual Page Number
- Page Offset

### Phase 3 - Address Classification ✅

Goal

Associate a virtual address with a memory region.

Current Regions

```text
STACK
HEAP_DATA
UNKNOWN
```

Implementation

Uses a simple heuristic classifier based on
observed Linux virtual address ranges.

Future Work

Phase 6 will replace heuristics with actual
process memory map inspection using:

```text
/proc/self/maps
```