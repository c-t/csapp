# CacheSim Design

## Objective

Build a cache simulator that demonstrates how
memory addresses interact with CPU caches.

---

## Problem

Main memory is significantly slower than the CPU.

Without caching:

```text
CPU
 ↓
Main Memory
```

every access incurs high latency.

---

## Solution

Use a cache:

```text
CPU
 ↓
Cache

Hit?
 ↓

Data

Miss?
 ↓

Main Memory
```

---

## Cache Address Layout

A memory address is divided into:

```text
Tag
Set Index
Block Offset
```

Example:

```text
+------+-----------+--------+
| Tag  | Set Index | Offset |
+------+-----------+--------+
```

---

## Roadmap

Phase 0 - Cache Investigation ✅

Phase 1 - Address Decomposition

Phase 2 - Cache Structures

Phase 3 - Cache Lookup

Phase 4 - Cache Fill

Phase 5 - Replacement Policies

Phase 6 - Cache Statistics

Phase 7 - Locality Experiments

Phase 8 - CacheSim v1.0

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

## Phase 2 - Cache Structures ✅

Goal

Model the physical organization of a cache.

Structure

```text
Cache
 └── Sets
      └── Lines
```

Cache Line

```c
typedef struct
{
    uint32_t tag;
    int valid;
} cache_line_t;
```

Learning Objective

Represent cache state in memory and prepare for
cache lookup operations.

## Phase 3 - Cache Lookup ✅

Goal

Determine whether a memory block already exists
in the cache.

Lookup Flow

```text
Address
 ↓
Set Lookup
 ↓
Tag Compare
```

Result

```text
CACHE HIT
```

or

```text
CACHE MISS
```

---

## Phase 4 - Cache Fill ✅

Goal

Handle cache misses by inserting blocks into the
cache.

Flow

```text
Address
 ↓
Lookup

MISS
 ↓
Memory Fetch
 ↓
Cache Fill
 ↓
Future HIT
```

Implementation

A cache fill updates:

```text
Tag
Valid Bit
```

for the selected cache line.

Learning Objective

Understand how caches populate entries after a
miss.