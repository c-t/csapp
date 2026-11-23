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

## Phase 2 - Address Visualization ✅

Goal

Visualize the internal structure of a virtual
address.

Format:

```text
| PML4 | PDPT | PD | PT | OFFSET |
```

Learning Objective

Demonstrate that page-table indices are stored
directly within the virtual address and are
consumed by the MMU during translation.

## Phase 3 - Page Table Structures ✅

Goal

Introduce simulated page-table structures and
populate entries using page-table indices.

Implementation

Create:

```text
PML4
PDPT
PD
PT
```

structures containing:

```text
Present Bit
Frame Number
```

Learning Objective

Understand how page-table indices select entries
within the page-table hierarchy.

## Phase 4 - Page Walk Simulation ✅

Goal

Simulate the sequence of lookups performed
during address translation.

Implementation

```text
PML4
 ↓
PDPT
 ↓
PD
 ↓
PT
 ↓
Frame
```

Each level verifies the presence of an entry
before proceeding to the next level.

Learning Objective

Understand how hardware performs a page walk
when a translation is not available in the TLB.

## Phase 5 - Physical Address Generation ✅

Goal

Generate a physical address from the frame
returned by a page walk.

Formula

```text
Physical Address
=
(Frame << 12)
+
Offset
```

Learning Objective

Understand that page translation modifies the
page portion of an address while preserving the
offset portion.

## Phase 6 - Multi-Address Translation ✅

Goal

Translate multiple virtual addresses and compare
their resulting physical translations.

Implementation

```text
VA
 ↓
Page Walk
 ↓
Frame
 ↓
Physical Address
```

for several addresses.

Learning Objective

Understand how different virtual addresses may
share frames or differ only by their offsets.