# AddrTx

Virtual Address Translation Explorer

AddrTx is a Chapter 9 (Virtual Memory) learning project inspired by the investigation-first approach used in StackViz, CallScope, and MiniObjDump.

The goal is to understand how virtual addresses are organized, translated, and ultimately mapped by the operating system and hardware.

---

## Project Status

- [x] Phase 0 - Virtual Address Investigation
- [x] Phase 1 - VPN + Offset Split
- [x] Phase 2 - Binary Visualization
- [x] Phase 3 - Address Classification
- [x] Phase 4 - Page Size Explorer
- [x] Phase 5 - Multi-Address Analysis
- [ ] Phase 6 - Process Memory Regions
- [ ] Phase 7 - Translation Statistics
- [ ] Phase 8 - AddrTx v1.0

---

## Project Goals

Learn and visualize:

- Virtual Addresses
- Virtual Page Numbers (VPN)
- Page Offsets
- Pages and Page Sizes
- Virtual Memory Layout
- Address Translation Fundamentals

---

## Phase 0 Findings

### Test Programs

Investigated addresses from:

- Global variables
- Heap allocations
- Stack variables

### Observed Addresses

```text
global      : 0x5dcf3a1ce010
heap object : 0x5dcf46d92010
heap ptr    : 0x7ffc144c4350
stack       : 0x7ffc144c434c
```

### Key Observations

#### Heap Object vs Heap Pointer

The allocated object resides in heap memory:

```text
0x5dcf46d92010
```

The pointer variable itself resides on the stack:

```text
0x7ffc144c4350
```

This demonstrates that:

```text
Pointer Variable
        ≠
Referenced Object
```

The pointer may live on the stack while the
object it references resides in the heap.

---

#### Stack Frame Layout

Observed:

```text
heap ptr : 0x7ffc144c4350
stack    : 0x7ffc144c434c
```

These addresses are adjacent because both
objects are stored inside the same stack frame.

---

#### Process Memory Layout

Observed address ranges suggest:

```text
High Addresses
+----------------------+
| Stack                |
+----------------------+

| Shared Libraries     |

+----------------------+
| Heap                 |
+----------------------+

| Globals / Data       |
+----------------------+

| Text Segment         |
+----------------------+
Low Addresses
```

---

## Key Learning

A virtual address is associated with a specific
region of a process address space.

Objects that are logically connected may reside
in completely different virtual memory regions.

Example:

```text
heap_ptr
    ↓
Stack

heap_object
    ↓
Heap
```

Understanding this distinction is fundamental to:

- Virtual Memory
- Paging
- Demand Paging
- Copy-On-Write
- Dynamic Memory Allocation

---

## Phase 1 - VPN + Offset Split

AddrTx now decomposes virtual addresses into:

```text
Virtual Page Number (VPN)
+
Page Offset
```

Formula:

```text
VPN    = Address >> 12

Offset = Address & 0xFFF
```

Example:

```text
Address : 0x7ffee7a5426c

VPN     : 0x7ffee7a54

Offset  : 0x26c
```

Key Learning:

A virtual address identifies:

- A page (VPN)
- A location within that page (Offset)

### Phase 2 - Binary Visualization

Displays address layout as:

```text
| VPN | OFFSET |
```

Example:

```text
011000000000111000001100100001100001|000000010000
```

Key Learning:

- Last 12 bits = page offset
- Remaining bits = virtual page number
```

### Phase 3 - Address Classification

Classifies virtual addresses into memory regions.

Current classifications:

```text
STACK
HEAP_DATA
UNKNOWN
```

Example:

```text
Address : 0x7ffc007b963c

Region  : STACK
```

Key Learning:

Virtual addresses belong to specific regions
inside a process address space.

---
### Phase 4 - Page Size Explorer

Analyzes address translation for:

- 4 KB pages
- 2 MB pages
- 1 GB pages

Key Learning

Larger pages increase the number of offset bits
and reduce the number of VPN bits.

Benefits include:

- Fewer page table entries
- Better TLB efficiency
- Lower translation overhead
---

### Phase 5 - Multi-Address Analysis

Compares multiple virtual addresses and
determines whether they share a page.

Example:

```text
0x7fff4ca70d90
0x7fff4ca70d8c
```

Both produce:

```text
VPN = 0x7fff4ca70
```

Result:

```text
Same Virtual Page
```

Key Learning:

Addresses with identical VPN values reside in
the same page and share the same page
translation.

---

### Phase 6 - Process Memory Regions

Investigate:

```text
/proc/self/maps
```

and visualize the process address space.

---

### Phase 7 - Translation Statistics

Analyze:

- Address distribution
- Page utilization
- Region utilization

---

### Phase 8 - AddrTx v1.0

Integrated virtual-address analysis tool.

---

## Learning Outcome

AddrTx aims to make an address such as:

```text
0x7ffc144c434c
```

feel as meaningful as:

```text
RDI = Argument 1
```

became during the CallScope project.

The project serves as the foundation for future
Chapter 9 projects:

- Multi-Level Page Table Simulator
- TLB Simulator
- Demand Paging Simulator
- Copy-On-Write Simulator
- Virtual Memory Manager