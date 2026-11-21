# AddrTx

Virtual Address Translation Explorer

AddrTx is a learning project inspired by Chapter 9 of
Computer Systems: A Programmer's Perspective (CS:APP).

The project explores how virtual addresses are represented,
translated, classified, and mapped within a Linux process.

---

## Overview

AddrTx demonstrates:

```text
Virtual Address
      ↓
VPN + Offset
      ↓
Page
      ↓
Memory Region
      ↓
Translation Statistics
```

and provides hands-on exposure to:

- Virtual Address Translation
- Virtual Page Numbers (VPNs)
- Page Offsets
- Page Sizes
- Linux Process Memory Layout
- Shared Pages
- Translation Statistics

---

## Features

### Address Translation

Decompose a virtual address into:

```text
VPN + Offset
```

### Binary Visualization

Visualize address structure:

```text
| VPN | OFFSET |
```

### Address Classification

Classify addresses into:

```text
STACK
HEAP_DATA
UNKNOWN
```

### Page Size Explorer

Compare translation using:

```text
4 KB pages
2 MB pages
1 GB pages
```

### Multi-Address Analysis

Determine:

- Shared VPNs
- Shared Pages
- Translation Relationships

### Process Memory Regions

Inspect:

```text
/proc/self/maps
```

to identify:

- Executable mappings
- Heap mappings
- Stack mappings

### Translation Statistics

Generate:

- Total Addresses
- Unique VPNs
- Shared Pages
- Page Utilization

### Runtime Dataset Analysis

Analyze addresses from:

```text
Global Variables
Heap Objects
Stack Variables
```

belonging to the running process.

---

## Project Structure

```text
addrtx/
├── Makefile
├── README.md
├── build
├── docs
│   ├── design.md
│   ├── investigations.md
│   └── notes.md
├── include
│   └── addrtx.h
├── samples
│   └── sample_output.txt
├── src
├── test
└── tests
```

---

## Learning Outcomes

After completing AddrTx, you should understand:

- Virtual Address Structure
- VPN and Offset Extraction
- Binary Address Layout
- Page Sizes and Huge Pages
- Shared Virtual Pages
- Linux Memory Mappings
- Process-Specific Address Spaces
- Translation Statistics

---

## Status

```text
AddrTx v1.0
```

Completed as part of the CS:APP Virtual Memory project series.