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

Tag     : 0x48d15

Set     : 0x27

Offset  : 0x8
```

Meaning:

```text
Search Set 39

Look for Tag 0x48d15

If found:
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
Set 39
 ↓
cache->sets[39]
```

The selected line can then be examined during a
cache lookup.

At initialization:

```text
Valid = no
```

for every cache line.