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
- [ ] Phase 1 - Index Extraction
- [ ] Phase 2 - Address Visualization
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