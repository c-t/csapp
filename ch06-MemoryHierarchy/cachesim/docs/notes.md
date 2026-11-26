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