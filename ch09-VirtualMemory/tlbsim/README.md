# TLBSim

Translation Lookaside Buffer Simulator

TLBSim is a Chapter 9 (Virtual Memory) learning
project inspired by CS:APP.

The project explores how processors avoid
performing expensive page walks for every memory
access by caching translations in a Translation
Lookaside Buffer (TLB).

---

## Overview

PTSim answered:

Virtual Address
↓
Page Walk
↓
Frame

TLBSim answers:

Virtual Address
↓
VPN
↓
TLB

Hit?
↓
Frame

Miss?
↓
Page Walk
↓
Frame

---

## Project Status

- [x] Phase 0 - TLB Investigation
- [x] Phase 1 - TLB Entry Structures
- [x] Phase 2 - TLB Lookup
- [x] Phase 3 - TLB Fill
- [x] Phase 4 - Repeated Accesses
- [x] Phase 5 - Replacement Policies
- [ ] Phase 6 - Translation Statistics
- [ ] Phase 7 - Locality Experiments
- [ ] Phase 8 - TLBSim v1.0

## Phase 1 - TLB Entry Structures

Implemented a fixed-size TLB containing cached
VPN-to-frame translations.

Example:

```text
VPN          Frame

0x7ffff84e3  0x10e3

0x58dc74280  0x1080
```

Key Learning:

A TLB stores previously computed page-walk
results and acts as a small translation cache.

## Phase 2 - TLB Lookup

Implemented VPN lookup within the TLB.

Examples:

### Hit

```text
VPN : 0x7ffff84e3

Result : HIT

Frame  : 0x10e3
```

### Miss

```text
VPN : 0x12345678

Result : MISS
```

Key Learning:

A TLB stores cached translation results and can
avoid a page walk when a translation is already
present.

## Phase 3 - TLB Fill

Implemented miss handling and translation caching.

Workflow:

```text
VPN
 ↓
TLB MISS
 ↓
Page Walk
 ↓
Frame
 ↓
Insert Into TLB
```

Example:

```text
VPN : 0x12345678

Result : MISS

Frame : 0x1678

Inserted Into TLB
```

Subsequent access:

```text
VPN : 0x12345678

Result : HIT

Frame : 0x1678
```

Key Learning:

TLBs avoid repeated page walks by caching
translation results.

## Phase 4 - Repeated Accesses

Demonstrates temporal locality through repeated
VPN accesses.

Access Pattern:

```text
A
B
A
A
B
```

Observed Result:

```text
MISS
MISS
HIT
HIT
HIT
```

Example Output:

```text
VPN        Result     Frame

0xaaa      MISS       0x1aaa
0xbbb      MISS       0x1bbb
0xaaa      HIT        0x1aaa
0xaaa      HIT        0x1aaa
0xbbb      HIT        0x1bbb
```

Pattern Statistics:

```text
Total Accesses : 5

Hits           : 3

Misses         : 2

Hit Rate       : 60.00%

Miss Rate      : 40.00%
```

Key Learning:

Recently translated pages tend to be accessed
again. The TLB exploits this temporal locality
to reduce page walks.

## Phase 5 - FIFO Replacement Policy

Implemented a finite-capacity TLB using FIFO
replacement.

Example:

```text
Insert A
Insert B
Insert C
Insert D
Insert E
```

Result:

```text
Evict A
Insert E
```

Final State:

```text
E B C D
```

Key Learning:

Translation caches are limited in size and must
evict older entries to make room for new ones.