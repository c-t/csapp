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
- [x] Phase 3 - Page Table Structures
- [x] Phase 4 - Page Walk Simulation
- [x] Phase 5 - Physical Address Generation
- [x] Phase 6 - Multi-Address Translation
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

## Phase 3 - Page Table Structures

Construct simulated page-table structures and
populate entries using extracted indices.

Example:

```text
PML4[255]
  ↓
PDPT[511]
  ↓
PD[450]
  ↓
PT[227]
  ↓
FRAME
```

Page Table Entry:

```text
Present : yes
Frame   : 0x12345
```

Key Learning:

Page-table indices are used to select entries
within page-table structures during address
translation.

## Phase 4 - Page Walk Simulation

Simulates traversal through a multi-level page
table hierarchy.

Example:

```text
PML4[255]
  ↓
PDPT[511]
  ↓
PD[450]
  ↓
PT[227]
  ↓
Frame 0x12345
```

Page Walk:

```text
Lookup PML4[255] ... OK
Lookup PDPT[511] ... OK
Lookup PD[450] ... OK
Lookup PT[227] ... OK

Frame Found : 0x12345
```

Key Learning:

Address translation is a sequence of page-table
lookups driven by indices embedded within the
virtual address.

## Phase 5 - Physical Address Generation

Generate a physical address after a successful
page walk.

Formula:

```text
Physical Address
=
(Frame << 12)
+
Offset
```

Example:

```text
Frame            : 0x12345

Offset           : 0x71c

Frame Base       : 0x12345000

Physical Address : 0x1234571c
```

Key Learning:

The page walk translates a virtual page into a
physical frame while preserving the page offset.

## Phase 6 - Multi-Address Translation

Translate and compare multiple virtual
addresses.

Example:

```text
Virtual Address      Frame      Physical Address
------------------------------------------------
0x7ffff84e371c       0x10e3     0x10e371c
0x7ffff84e3720       0x10e3     0x10e3720
0x7ffff84e4000       0x10e4     0x10e4000
0x58dc74280010       0x1080     0x1080010
```

Key Learning:

Multiple virtual addresses may translate to the
same physical frame and differ only by offset.