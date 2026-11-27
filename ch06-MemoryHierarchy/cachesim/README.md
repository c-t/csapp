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
- [x] Phase 5 - Replacement Policies
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

---

## Phase 5 - Replacement Policies

Implemented cache replacement for a 16-set,
4-way set-associative cache.

The address layout is now:

```text
+----------------------+----------+--------+
|         Tag          |   Set    | Offset |
+----------------------+----------+--------+

         24                4          4
```

Replacement Policies:

- **FIFO (First-In, First-Out)** tracks a victim
  way separately for each set and evicts the oldest
  inserted block.
- **LRU (Least Recently Used)** tracks a per-line
  access timestamp and evicts the least recently
  used block. Cache hits refresh the line age.

Run the demonstrations:

```bash
make
./build/cachesim fifo
./build/cachesim lru
make test
```

Key Learning:

Replacement behavior matters when a set is full.
FIFO depends on insertion order, while LRU preserves
recently used blocks and is affected by hits as well
as fills.

## Testing Replacement Policies

Build and execute the replacement unit test with:

```bash
make test
```

The target builds `build/test_replacement` from
`tests/test_replacement.c` and supporting cache sources,
then runs the test binary. It can also be run directly:

```bash
./build/test_replacement
```

The test verifies FIFO fill and victim behavior and
LRU hit-age refresh plus eviction behavior using
assertions. It is successful when the process exits
normally without an assertion failure. Messages such as
`FIFO Fill`, `LRU Fill`, and `LRU Evict` are informational
output from the functions under test.

Run policy demonstrations separately:

```bash
./build/cachesim fifo
./build/cachesim lru
```

---

## Phase 6 - Cache Statistics

Implemented cache statistics collection.

Statistics:

- **Hit Rate**

  Percentage of memory accesses that result in a cache hit.

- **Miss Rate**

  Percentage of memory accesses that result in a cache miss.

- **Eviction Count**

  Number of times a cache block is evicted.

Key Learning:

Cache statistics provide insight into cache
performance and efficiency.

---

## Phase 7 - Locality Experiments

Conducted experiments to observe temporal and
spatial locality.

Experiments:

- **Temporal Locality**

  Accessing the same memory location multiple
  times.

- **Spatial Locality**

  Accessing memory locations close to each other.

Key Learning:

Locality principles explain why caches are
effective in reducing memory-access latency.

---

## Phase 8 - CacheSim v1.0

Released CacheSim version 1.0.

Features:

- Configurable cache size, block size, and
  associativity.

- Multiple cache replacement policies.

- Cache statistics collection and reporting.

- Memory access patterns for testing.

Future Work:

- Advanced cache features (e.g., prefetching,
  write policies).

- Performance optimizations.

- User interface improvements.

---

## Acknowledgments

Inspired by the cache simulation project in
CS:APP.

Special thanks to the authors and contributors
of CS:APP for the valuable educational resource.

---

## License

CacheSim is licensed under the MIT License.