# CacheSim

Cache Simulator

CacheSim is a Chapter 6 (Memory Hierarchy)
learning project inspired by CS:APP.

The project explores how CPU caches reduce
memory-access latency by storing recently
accessed data close to the processor.

---

## Overview

Memory Access

```text
Address
   ↓
Cache Lookup

Hit?
 ↓

Data

Miss?
 ↓

Main Memory
```

---

## Cache Organization

A memory address is divided into:

```text
+------+-----------+--------+
| Tag  | Set Index | Offset |
+------+-----------+--------+
```

Each field determines where data may be found
within a cache.

---

## Learning Goals

- Cache organization
- Address decomposition
- Cache lookup
- Cache hits and misses
- Replacement policies
- Cache statistics
- Locality experiments

---

## Project Status

- [x] Phase 0 - Cache Investigation
- [x] Phase 1 - Address Decomposition
- [x] Phase 2 - Cache Structures
- [x] Phase 3 - Cache Lookup
- [x] Phase 4 - Cache Fill
- [ ] Phase 5 - Replacement Policies
- [ ] Phase 6 - Cache Statistics
- [ ] Phase 7 - Locality Experiments
- [ ] Phase 8 - CacheSim v1.0

## Phase 1 - Address Decomposition

Implemented cache address decomposition for a
direct-mapped cache.

Cache Configuration:

```text
Cache Size      : 1 KB
Block Size      : 16 Bytes
Cache Lines     : 64

Address Width   : 32 Bits
```

Address Layout:

```text
+----------------------+----------+--------+
|         Tag          |   Set    | Offset |
+----------------------+----------+--------+

        22               6          4
```

Example:

```text
Address : 0x12345678

Tag     : 0x48d15

Set     : 0x27

Offset  : 0x8
```

Key Learning:

Every cache lookup begins by extracting the
tag, set index, and block offset from the
memory address.

## Phase 2 - Cache Structures

Implemented the cache data model.

Cache Organization:

```text
Cache
 ├── Set 0
 │    └── Line
 ├── Set 1
 │    └── Line
 ...
 └── Set 63
      └── Line
```

Cache Line:

```c
typedef struct
{
    uint32_t tag;
    int valid;
} cache_line_t;
```

Key Learning:

A cache lookup ultimately searches a cache line
inside a selected cache set.

## Phase 3 - Cache Lookup

Implemented cache lookup for a direct-mapped cache.

Lookup Process:

```text
Address
 ↓
Tag + Set
 ↓
Select Cache Line
 ↓
Compare Tag
```

Result:

```text
CACHE HIT
```

or

```text
CACHE MISS
```

A cache hit requires:

```text
Valid Bit = yes

Stored Tag = Requested Tag
```

---

## Phase 4 - Cache Fill

Implemented cache miss handling and cache fill.

Workflow:

```text
Address
 ↓
Lookup
 ↓
CACHE MISS
 ↓
Cache Fill
 ↓
Future CACHE HIT
```

Example:

```text
CACHE MISS

Set : 39

Tag : 0x48d15
```

After filling:

```text
CACHE HIT
```

Updated Cache State:

```text
Set 39

Tag   = 0x48d15

Valid = yes
```

Key Learning:

Caches learn from misses.

Once a block is inserted into the cache,
subsequent accesses become cache hits.