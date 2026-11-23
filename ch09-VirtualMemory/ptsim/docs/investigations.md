# Phase 0 - 48-bit Address Investigation

## Objective

Understand how x86-64 virtual addresses are
partitioned prior to page-table translation.

---

## Test Program

Observed:

```text
global : 0x5c7a519cb010
stack  : 0x7fff9b48d904
```

---

## Virtual Address Layout

x86-64 uses four page-table levels:

```text
| PML4 | PDPT | PD | PT | OFFSET |

   9      9     9    9      12
```

---

## Why 12 Offset Bits?

Standard page size:

```text
4096 bytes
```

Since:

```text
4096 = 2^12
```

the page offset occupies:

```text
12 bits
```

---

## Why 9-Bit Indices?

Each page-table level uses:

```text
9 bits
```

Therefore:

```text
2^9 = 512
```

entries can be stored in each table.

---

## Findings

A virtual address is not treated as a single
number during translation.

Instead it is interpreted as:

```text
PML4 Index
PDPT Index
PD Index
PT Index
Offset
```

Each field participates in the page-walk
process.

---

## Key Learning

AddrTx focused on:

```text
VPN + Offset
```

PTSim begins examining the internal structure
of the VPN itself.

# Phase 1 - Index Extraction

## Global Address

```text
Address : 0x58dc74280010

PML4    : 177
PDPT    : 369
PD      : 417
PT      : 128

Offset  : 0x10
```

---

## Stack Address

```text
Address : 0x7ffff84e371c

PML4    : 255
PDPT    : 511
PD      : 450
PT      : 227

Offset  : 0x71c
```

---

## Findings

The VPN can be decomposed into:

```text
PML4
PDPT
PD
PT
```

Each field uses:

```text
9 bits
```

allowing:

```text
512 entries
```

per page-table level.

---

## Key Learning

A page walk is driven entirely by indices
extracted from the virtual address.

The offset is not involved in the lookup and
is carried unchanged to the final physical
address.

# Phase 2 - Address Visualization

## Example Address

```text
0x7ffff84e371c
```

Extracted Fields:

```text
PML4   = 255
PDPT   = 511
PD     = 450
PT     = 227
Offset = 0x71c
```

Binary Visualization:

```text
011111111|111111111|111000010|011100011|011100011100
```

Field Breakdown:

```text
PML4   : 011111111

PDPT   : 111111111

PD     : 111000010

PT     : 011100011

OFFSET : 011100011100
```

## Findings

Each page-table level consumes:

```text
9 bits
```

The page offset consumes:

```text
12 bits
```

Together they form the complete 48-bit virtual
address used during translation.

## Key Learning

Page-table indices are encoded directly within
the virtual address.

A page walk simply interprets these fields in
sequence.

# Phase 3 - Page Table Structures

## Example Address

```text
0x7ffff84e371c
```

Extracted:

```text
PML4 = 255
PDPT = 511
PD   = 450
PT   = 227
```

## Simulated Hierarchy

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

## Page Table Entry

```text
Index   : 227

Present : yes

Frame   : 0x12345
```

## Findings

Page-table indices are not merely fields within
an address.

They are used to select entries from page-table
structures.

## Key Learning

Address translation consists of navigating a
hierarchy of page-table entries using indices
embedded within the virtual address.

# Phase 4 - Page Walk Simulation

## Example Address

```text
0x7ffff84e371c
```

Indices:

```text
PML4 = 255
PDPT = 511
PD   = 450
PT   = 227
```

Simulated Walk:

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

Execution Trace:

```text
Lookup PML4[255] ... OK
Lookup PDPT[511] ... OK
Lookup PD[450] ... OK
Lookup PT[227] ... OK

Frame Found : 0x12345
```

## Findings

Each page-table level uses an index extracted
from the virtual address.

Successful traversal produces a frame number.

## Key Learning

A page walk is a hierarchical lookup process
that converts a virtual page reference into a
physical frame reference.

# Phase 5 - Physical Address Generation

## Example

Virtual Address

```text
0x7ffff84e371c
```

Page Walk Result

```text
Frame = 0x12345
```

Offset

```text
0x71c
```

Generated Physical Address

```text
Frame Base

0x12345 << 12

=
0x12345000
```

```text
Physical Address

0x12345000
+
0x71c

=
0x1234571c
```

## Findings

The offset remains unchanged throughout the
translation process.

Only the page portion of the address is
translated.

## Key Learning

Page walks convert:

```text
Virtual Page
```

into:

```text
Physical Frame
```

while preserving:

```text
Offset
```

# Phase 6 - Multi-Address Translation

## Dataset

```text
0x7ffff84e371c
0x7ffff84e3720
0x7ffff84e4000
0x58dc74280010
```

## Results

```text
0x7ffff84e371c -> Frame 0x10e3 -> 0x10e371c

0x7ffff84e3720 -> Frame 0x10e3 -> 0x10e3720

0x7ffff84e4000 -> Frame 0x10e4 -> 0x10e4000

0x58dc74280010 -> Frame 0x1080 -> 0x1080010
```

## Observations

Addresses:

```text
0x7ffff84e371c
0x7ffff84e3720
```

shared:

```text
Frame = 0x10e3
```

while differing only in their offsets.

## Findings

Multiple virtual addresses may map to the same
physical frame.

Physical location is determined by:

```text
Frame + Offset
```

rather than the virtual address alone.

## Key Learning

Physical memory translations can be shared even
when virtual addresses differ.