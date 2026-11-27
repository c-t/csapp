# Notes

## Core Question

How does a cache determine whether requested
data is already present?

---

## Cache Lookup

```text
Address
 ↓
Tag
 ↓
Set
 ↓
Offset
```

### Hit

Requested block already exists in cache.

### Miss

Requested block must be fetched from memory.

---

## Why Caches Matter

Caches reduce average memory-access latency.

```text
Cache Hit
```

is significantly faster than:

```text
Main Memory Access
```

---

## Connection To Previous Projects

AddrTx:

```text
VA
 ↓
VPN + Offset
```

PTSim:

```text
VPN
 ↓
Page Tables
 ↓
Frame
```

TLBSim:

```text
VPN
 ↓
TLB
 ↓
Frame
```

CacheSim:

```text
Address
 ↓
Tag
 ↓
Set
 ↓
Offset
```

## Phase 1 Insight

A cache does not search its entire contents.

Instead:

```text
Address
 ↓
Set Index
 ↓
Select Set
 ↓
Tag Compare
```

Only the selected set must be examined.

Example:

```text
Address : 0x12345678

Tag     : 0x12345

Set     : 0x7

Offset  : 0x8
```

Meaning:

```text
Search Set 7

Look through Ways 0 through 3

If any line has a matching tag:
    Cache HIT

Otherwise:
    Cache MISS
```

The offset specifies the byte inside the cache
block.

## Phase 2 Insight

Address decomposition identifies:

```text
Tag
Set
Offset
```

Cache structures provide:

```text
Set
 ↓
Line
```

Example:

```text
Address
 ↓
Set 7
 ↓
cache->sets[7].lines[0..3]
```

Each line in the selected set can then be examined
during a cache lookup.

At initialization:

```text
Valid = no
```

for every cache line.

## Phase 3 Insight

Cache lookup consists of:

```text
Select Set
 ↓
Compare Tags
```

Hit Condition:

```text
Valid = yes

Stored Tag = Requested Tag
```

Miss Condition:

```text
Valid = no

or

Tag Mismatch
```

---

## Phase 4 Insight

Caches learn from misses.

Example:

```text
Lookup
 ↓
MISS
 ↓
Fill Cache
 ↓
Lookup
 ↓
HIT
```

Before Fill:

```text
Valid = no
```

After Fill:

```text
Valid = yes
```

The cache now contains a reusable copy of the
requested memory block.

Future accesses avoid expensive memory fetches.

---

## Phase 5 Insight

CacheSim now uses 16 sets with 4 ways per set:

```text
Cache Size  : 1024 Bytes
Block Size  : 16 Bytes
Cache Lines : 64
Cache Sets  : 16
Ways/Set    : 4
```

A lookup searches every valid line in the
selected set:

```text
Select Set
   ↓
Search Four Ways
   ↓
Tag Match?

Yes → Cache HIT
No  → Cache MISS
```

### FIFO

FIFO evicts the first block inserted into a set.
It maintains one victim index per set:

```text
Way 0 → Way 1 → Way 2 → Way 3 → Way 0
```

FIFO fill order does not change when a line is
accessed through a cache hit.

### LRU

LRU evicts the line with the smallest access
timestamp:

```text
Lowest Age → Least Recently Used → Evict
```

A cache hit refreshes the matching line's timestamp,
so frequently reused blocks are more likely to remain
resident.

Example:

```text
Fill A in Way 0
Fill B in Way 1
Fill C in Way 2
Hit  A
Fill D in Way 3
Fill E

LRU evicts B because A is now more recent
FIFO may instead evict A according to insertion age
```

## Phase 6 Insight

Cache statistics separate lookup outcomes from
replacement events:

```text
Lookup
  ↓
Hit or Miss

Full Set
  ↓
Eviction
```

Metrics:

```text
Hit Rate  = Hits / Total Accesses * 100
Miss Rate = Misses / Total Accesses * 100
```

Example LRU result:

```text
Total Accesses : 6
Hits           : 1
Misses         : 5
Evictions      : 1
Hit Rate       : 16.67%
Miss Rate      : 83.33%
```

The hit refreshes a line, making that block more
recent in the LRU timestamps. The miss after set
fill then evicts the least-recently-used line.

---

## Phase 7 Insight

Temporal locality measures reuse of the same blocks:

```text
A B A A B A
```

Repeated access produces a 66.67% hit rate in the
implemented workload.

Spatial locality measures reuse of nearby addresses:

```text
0x00 → 0x04 → 0x08 → 0x0c → 0x10
```

The 0x04, 0x08, and 0x0c offsets are hits within the
block first fetched at 0x00. The 0x10 address starts
a different block and produces a miss.

Run:

```bash
./build/cachesim temporal
./build/cachesim spatial
./build/cachesim locality
make test
```