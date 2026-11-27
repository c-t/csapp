# Phase 0 - Cache Investigation

## Objective

Understand cache organization and cache
addressing.

---

## Observation

A cache cannot store every memory location.

Memory addresses must therefore be mapped to
specific cache locations.

---

## Cache Components

### Cache Line

Stores a block of memory.

### Cache Set

A collection of cache lines.

### Cache Tag

Identifies which memory block occupies a cache
line.

### Block Offset

Selects a byte within a cache block.

---

## Address Breakdown

```text
+------+-----------+--------+
| Tag  | Set Index | Offset |
+------+-----------+--------+
```

---

## Cache Lookup

```text
Address
   ↓
Set Index
   ↓
Select Set
   ↓
Tag Compare

Hit?
 ↓

Data

Miss?
 ↓

Memory Fetch
```

---

## Key Learning

Cache behavior begins with address
decomposition.

Every cache lookup depends on:

```text
Tag
Set Index
Offset
```

## Phase 1 - Address Decomposition ✅

Goal

Decompose a memory address into the fields used
during cache lookup.

Address Format

```text
+----------------------+----------+--------+
|         Tag          |   Set    | Offset |
+----------------------+----------+--------+

        24               4          4
```

Field Purpose

Tag:

```text
Identifies a memory block.
```

Set Index:

```text
Selects a cache set.
```

Block Offset:

```text
Selects a byte within a cache block.
```

Learning Objective

Understand how memory addresses are interpreted
by a cache before any lookup occurs.

# Phase 2 - Cache Structures

## Cache Configuration

```text
Cache Size   : 1024 Bytes
Block Size   : 16 Bytes
Cache Lines  : 64
Cache Sets   : 16
Ways Per Set : 4
```

## Organization

```text
16 Sets

4 Lines Per Set

Set-Associative
```

## Initial State

All cache lines are initialized as:

```text
Tag   = 0
Valid = 0
Age   = 0
```

Example:

```text
Set 0

Way 0: Tag = 0, Valid = no
Way 1: Tag = 0, Valid = no
Way 2: Tag = 0, Valid = no
Way 3: Tag = 0, Valid = no
```

## Findings

Each set contains four cache lines. The valid bit
determines whether a line contains meaningful data,
and the age value supports LRU replacement.

## Key Learning

Set-associative cache structures allow several
memory blocks that share a set index to coexist.

# Phase 3 - Cache Lookup

## Cache Hit Requirements

```text
Valid Bit = yes

Stored Tag = Requested Tag
```

### Lookup Algorithm

```text
Address
 ↓
Extract Set
 ↓
Select Cache Line
 ↓
Compare Tag
```

### Result

```text
CACHE HIT
```

or

```text
CACHE MISS
```

---

# Phase 4 - Cache Fill

## Initial Cache State

```text
Set 7

Way 0: Tag = 0, Valid = no
Way 1: Tag = 0, Valid = no
Way 2: Tag = 0, Valid = no
Way 3: Tag = 0, Valid = no
```

---

## First Lookup

Address:

```text
0x12345678
```

Result:

```text
CACHE MISS
```

Reason:

```text
Valid Bit = no
```

---

## Cache Fill

Inserted:

```text
Set 7
Way 0

Tag = 0x12345
```

Updated State:

```text
Set 7

Way 0: Tag = 0x12345, Valid = yes
Way 1: Tag = 0x0,     Valid = no
Way 2: Tag = 0x0,     Valid = no
Way 3: Tag = 0x0,     Valid = no
```

---

## Second Lookup

Address:

```text
0x12345678
```

Result:

```text
CACHE HIT
```

Reason:

```text
Stored Tag = Requested Tag

Valid Bit  = yes
```

---

## Findings

A cache miss becomes a cache hit after the
requested block is inserted.

Caches exploit reuse by storing recently
accessed memory blocks.

## Key Learning

```text
MISS
 ↓
Fill
 ↓
HIT
```

is the fundamental cache lifecycle.

# Phase 5 - Replacement Policies ✅

Goal

When a cache miss targets a full set, decide which
of the four ways should be replaced.

Policies

- **Least Recently Used (LRU)**

  Evict the line with the smallest age timestamp.
  A cache hit updates the matching line's age.

- **First In, First Out (FIFO)**

  Evict the per-set victim way. After eviction,
  advance from Way 0 through Way 3 and back to Way 0.

Implementation

```text
MISS
  ↓
Find an empty way
  ↓
No empty way
  ↓
Apply FIFO or LRU
  ↓
Replace victim
```

Demonstrate:

```bash
make test
./build/test_replacement
./build/cachesim fifo
./build/cachesim lru
```

The `make test` target builds and executes
`tests/test_replacement.c` against the cache implementation.
It checks FIFO victim selection and LRU age/eviction behavior
using assertions. A normal exit means the assertions passed;
an assertion failure reports the failed condition and exits
with an error.

Learning Objective

Observe how cache hits and insertion order determine
which block remains resident in a full set.

# Phase 6 - Cache Statistics ✅

Each cache lookup updates:

```text
Accesses
  ↓
HIT or MISS
  ↓
Hits or Misses
```

Each full-set replacement updates:

```text
Eviction
  ↓
Eviction Count
```

Observed FIFO example:

```text
Total Accesses : 5
Hits           : 0
Misses         : 5
Evictions      : 1
Hit Rate       : 0.00%
Miss Rate      : 100.00%
```

Observed LRU example:

```text
Total Accesses : 6
Hits           : 1
Misses         : 5
Evictions      : 1
Hit Rate       : 16.67%
Miss Rate      : 83.33%
```

Run:

```bash
make test
./build/cachesim fifo
./build/cachesim lru
```