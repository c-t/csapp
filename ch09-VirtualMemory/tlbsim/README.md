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
  - [x] FIFO
  - [x] LRU
- [x] Phase 6 - Translation Statistics
- [x] Phase 7 - Locality Experiments
- [x] Phase 8 - TLBSim v1.0

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

## Phase 5 - Replacement Policies

Implemented two TLB replacement strategies.

### FIFO (First In First Out)

Evicts the oldest inserted translation.

Example:

```text
A B C D

Insert E

Evict A
```

### LRU (Least Recently Used)

Evicts the least recently used translation.

Example:

```text
A B C D

Access:
A
A
B

Insert E

Evict C
```

Key Learning:

Different eviction strategies can significantly
affect hit rate and overall cache performance.

## Phase 6 - Translation Statistics

Measured TLB effectiveness across a workload and
compared replacement policies.

FIFO:

```text
Hit Rate : 20%
```

LRU:

```text
Hit Rate : 40%
```

Key Learning:

Replacement policy directly impacts cache
effectiveness.

## Phase 7 - Locality Experiments

Measured the impact of workload locality on TLB
performance.

### Sequential Access Pattern

```text
AAA
AAA
AAA
AAA
AAA
AAA
AAA
AAA
```

Results:

```text
Accesses : 8

Hits     : 7

Misses   : 1

Hit Rate : 87.50%
```

### Random Access Pattern

```text
AAA
BBB
CCC
DDD
EEE
FFF
111
222
```

Results:

```text
Accesses : 8

Hits     : 0

Misses   : 8

Hit Rate : 0.00%
```

Key Learning:

The effectiveness of a TLB depends heavily on
access locality.

Repeated accesses benefit from cached
translations, while random accesses do not.