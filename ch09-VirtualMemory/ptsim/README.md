# PTSim

Multi-Level Page Table Simulator

PTSim is a Chapter 9 (Virtual Memory) learning
project inspired by CS:APP.

The project explores how x86-64 virtual addresses
are translated through multi-level page tables.

---

## Overview

AddrTx answered:

```text
Virtual Address
      ↓
VPN + Offset
```

PTSim answers:

```text
Virtual Address
      ↓
PML4
      ↓
PDPT
      ↓
PD
      ↓
PT
      ↓
Physical Frame
```

---

## Project Status

- [x] Phase 0 - 48-bit Address Investigation
- [x] Phase 1 - Index Extraction
- [x] Phase 2 - Address Visualization
- [ ] Phase 3 - Page Table Structures
- [ ] Phase 4 - Page Walk Simulation
- [ ] Phase 5 - Physical Address Generation
- [ ] Phase 6 - Multi-Address Translation
- [ ] Phase 7 - Translation Statistics
- [ ] Phase 8 - PTSim v1.0

---

## Learning Goals

Learn:

- x86-64 Virtual Addresses
- Multi-Level Page Tables
- Page Walks
- Page Table Entries
- Physical Address Translation
- Translation Statistics

---

## Sample Addresses

Observed during Phase 0:

```text
global : 0x5c7a519cb010
stack  : 0x7fff9b48d904
```

---

## Current Status

```text
PTSim Phase 0 Complete
```

## Phase 1 - Index Extraction

Extract page-table indices from a virtual address.

Example:

```text
Virtual Address : 0x7ffff84e371c

PML4 Index      : 255
PDPT Index      : 511
PD Index        : 450
PT Index        : 227

Offset          : 0x71c
```

Key Learning:

The VPN is not a single value.

It consists of four 9-bit indices used during
the page walk.

## Phase 2 - Address Visualization

Visualize a 48-bit virtual address as:

```text
| PML4 | PDPT | PD | PT | OFFSET |
```

Example:

```text
011111111|111111111|111000010|011100011|011100011100
```

Key Learning:

The page-table indices exist as bit fields
within the virtual address and are consumed
during a page walk.