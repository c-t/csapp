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
- [ ] Phase 1 - Address Decomposition
- [ ] Phase 2 - Cache Structures
- [ ] Phase 3 - Cache Lookup
- [ ] Phase 4 - Cache Fill
- [ ] Phase 5 - Replacement Policies
- [ ] Phase 6 - Cache Statistics
- [ ] Phase 7 - Locality Experiments
- [ ] Phase 8 - CacheSim v1.0