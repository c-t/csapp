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
- [x] Phase 6 - Cache Statistics
- [x] Phase 7 - Locality Experiments
- [x] Phase 8 - CacheSim v1.0

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

## Phase 2 - Cache Structures

Implemented the 16-set, 4-way cache data model.

Cache Organization:

```text
Cache
 ├── Set 0
 │    ├── Way 0
 │    ├── Way 1
 │    ├── Way 2
 │    └── Way 3
 ...
 └── Set 15
      └── Four Ways
```

Cache Line:

```c
typedef struct
{
    uint32_t tag;
    uint64_t age;
    int valid;
} cache_line_t;
```

Key Learning:

A lookup searches every valid line in the selected set.

## Phase 3 - Cache Lookup

Implemented cache lookup for the 4-way set-associative cache.

Lookup Process:

```text
Address
 ↓
Tag + Set
 ↓
Select Set
 ↓
Compare Tags Across Four Ways
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

Set : 7
Way : 0
Tag : 0x12345
```

After filling:

```text
CACHE HIT
```

Updated Cache State:

```text
Set 7
Way 0

Tag   = 0x12345
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

Implemented cache statistics collection for lookup
accesses and replacement events.

Statistics:

- **Total Accesses** — number of cache lookups
- **Hits** — lookups that find a matching valid tag
- **Misses** — lookups that do not find a matching block
- **Evictions** — full-set fills that replace a valid line
- **Hit Rate** — `hits / accesses * 100`
- **Miss Rate** — `misses / accesses * 100`

Run a policy demo to print statistics:

```bash
./build/cachesim fifo
./build/cachesim lru
```

Example output:

```text
Cache Statistics
====================================

Total Accesses : 6
Hits           : 1
Misses         : 5
Evictions      : 1
Hit Rate       : 16.67%
Miss Rate      : 83.33%
```

The statistics tests also run with:

```bash
make test
```

Key Learning:

Cache statistics quantify reuse and replacement behavior.
Hit and miss rates summarize the effect of access patterns,
while eviction counts reveal when sets become full.

---

## Phase 7 - Locality Experiments

Implemented temporal and spatial locality workloads
using LRU replacement.

### Temporal Locality

Repeatedly accesses `0x00000000` and `0x00000100`:

```text
Total Accesses : 6
Hits           : 4
Misses         : 2
Hit Rate       : 66.67%
Miss Rate      : 33.33%
```

This demonstrates reuse of recently accessed blocks.

### Spatial Locality

Accesses nearby byte addresses inside and across cache
blocks:

```text
0x00000000
0x00000004
0x00000008
0x0000000c
0x00000010
```

The first four offsets reuse the block starting at
`0x00000000`, while `0x00000010` starts the next block:

```text
Total Accesses : 5
Hits           : 3
Misses         : 2
Hit Rate       : 60.00%
Miss Rate      : 40.00%
```

Run:

```bash
./build/cachesim temporal
./build/cachesim spatial
./build/cachesim locality
make test
```

Key Learning:

Temporal locality improves reuse of individual blocks,
while spatial locality improves reuse when nearby
addresses map to the same cache block.

---

## Phase 8 - CacheSim v1.0

Released CacheSim version 1.0.

The release implements a fixed 1 KB, 16-byte-block,
16-set, 4-way set-associative cache.

Features:

- Address decomposition into tag, set, and offset
- 32-bit cache lookup with valid/tag comparison
- FIFO and LRU replacement policies
- Hit, miss, eviction, hit-rate, and miss-rate reporting
- Temporal and spatial locality experiment workloads
- Address, replacement, locality, help, version, and all-demo modes
- Unit tests for replacement, statistics, and locality behavior

Run:

```bash
./build/cachesim help
./build/cachesim version
./build/cachesim all
make release
```

`make release` builds CacheSim, runs every test binary,
and prints the version and help text.

Future Work:

- Configurable cache size, block size, and associativity
- Additional replacement policies
- Prefetching and write policies
- Memory traces and broader access-pattern experiments