# PTSim Design

## Objective

Build a simulator that demonstrates how x86-64
virtual address translation works using
multi-level page tables.

---

## Address Structure

Modern x86-64 systems commonly use a 48-bit
canonical virtual address.

```text
| PML4 | PDPT | PD | PT | OFFSET |

   9      9     9    9      12
```

Total:

```text
9 + 9 + 9 + 9 + 12
=
48 bits
```

---

## Translation Model

```text
Virtual Address
       |
       v

PML4 Index
       |
       v

PDPT Index
       |
       v

PD Index
       |
       v

PT Index
       |
       v

Physical Frame
       |
       v

Physical Address
```

---

## Roadmap

Phase 0 - 48-bit Address Investigation ✅

Phase 1 - Index Extraction

Phase 2 - Address Visualization

Phase 3 - Page Table Structures

Phase 4 - Page Walk Simulation

Phase 5 - Physical Address Generation

Phase 6 - Multi-Address Translation

Phase 7 - Translation Statistics

Phase 8 - PTSim v1.0

## Phase 1 - Index Extraction ✅

Goal

Extract the fields used during a four-level
page walk.

Address Layout

```text
| PML4 | PDPT | PD | PT | OFFSET |
```

Implementation

```c
pml4  = (address >> 39) & 0x1FF;
pdpt  = (address >> 30) & 0x1FF;
pd    = (address >> 21) & 0x1FF;
pt    = (address >> 12) & 0x1FF;
offset = address & 0xFFF;
```

Learning Objective

Understand how a virtual address is decomposed
into page-table indices before translation.