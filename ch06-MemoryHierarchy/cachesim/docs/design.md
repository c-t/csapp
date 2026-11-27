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

Phase 5 - Replacement Policies ✅

Phase 6 - Cache Statistics

Phase 7 - Locality Experiments

Phase 8 - CacheSim v1.0

## Phase 1 - Address Decomposition

Implemented cache address decomposition for a
16-set, 4-way set-associative cache.

Cache Configuration:

```text
Cache Size      : 1 KB
Block Size      : 16 Bytes
Cache Lines     : 64
Cache Sets      : 16
Ways Per Set    : 4
Address Width   : 32 Bits
```

Address Layout:

```text
+----------------------+----------+--------+
|         Tag          |   Set    | Offset |
+----------------------+----------+--------+

        24               4          4
```

Example:

```text
Address : 0x12345678

Tag     : 0x12345
Set     : 0x7
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
    uint64_t age;
    int valid;
} cache_line_t;

typedef struct
{
    cache_line_t lines[CACHE_WAYS];
} cache_set_t;
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

## Phase 5 - Replacement Policies ✅

Goal

Decide which cache line to evict on a cache miss
when all four ways in the selected set are occupied.

Policies

- **Least Recently Used (LRU)**

  Evict the line with the smallest age timestamp.
  Cache hits refresh the matching line's timestamp.

- **First In, First Out (FIFO)**

  Evict the victim way selected for the set. The
  victim advances after each eviction:
  Way 0 → Way 1 → Way 2 → Way 3 → Way 0.

Implementation

On a miss, FIFO and LRU fill an empty way when
available. If the set is full, they select a victim
and replace that way's tag and valid state.

Run:

```bash
make test
./build/test_replacement
./build/cachesim fifo
./build/cachesim lru
```

Testing

`make test` compiles `tests/test_replacement.c` with the
address, cache, FIFO, and LRU sources. The resulting
`build/test_replacement` executable performs assertion
checks for FIFO and LRU behavior. The test passes if it
returns normally; an assertion or exit failure indicates
a replacement-policy defect.

Learning Objective

Compare replacement strategies and observe how
future hit and miss behavior depends on which block
is retained.