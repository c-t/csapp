# Notes

## Core Idea

The TLB is a cache of recent translations.

VPN
↓
Frame

---

## TLB Hit

VPN found in TLB.

Result:

Frame returned immediately.

No page walk required.

---

## TLB Miss

VPN not found.

Result:

Page walk required.

Translation inserted into TLB.

---

## Why TLBs Matter

Without a TLB:

Every memory access may require a page walk.

With a TLB:

Most memory accesses use cached translations.

---

## Connection To Previous Projects

AddrTx:

Virtual Address
↓
VPN + Offset

PTSim:

VPN
↓
Page Walk
↓
Frame

TLBSim:

VPN
↓
TLB
↓
Frame

## Phase 1 Insight

A TLB entry represents a completed translation.

```text
VPN
 ↓
Frame
```

The entry allows future accesses to avoid
repeating a page walk.

The Valid Bit determines whether an entry
contains a usable translation.

## Phase 2 Insight

The TLB functions as a translation cache.

```text
VPN
 ↓
TLB Lookup
```

Result:

```text
HIT
```

or

```text
MISS
```

A hit avoids a page walk entirely.

A miss requires address translation to be
performed and subsequently cached.

## Phase 3 Insight

TLBs learn from misses.

First access:

```text
MISS
 ↓
Page Walk
 ↓
Fill TLB
```

Later access:

```text
HIT
```

A single page walk can eliminate many future
translations for the same page.

## Phase 4 Insight

The effectiveness of a TLB depends on locality.

Example:

```text
A
B
A
A
B
```

produces:

```text
MISS
MISS
HIT
HIT
HIT
```

Instead of:

```text
5 page walks
```

only:

```text
2 page walks
```

were required.

Observed:

```text
Hit Rate  = 60%

Miss Rate = 40%
```

The more frequently a translation is reused,
the more valuable the TLB becomes.

This principle is known as:

```text
Temporal Locality
```

## Phase 5 Insight

TLBs are finite.

When capacity is exhausted:

```text
Eviction
```

becomes necessary.

### FIFO

```text
Evict oldest translation.
```

Simple but may discard frequently used entries.

### LRU

```text
Evict least recently used translation.
```

Preserves recently accessed entries and better
aligns with temporal locality.

### Example

FIFO:

```text
A B C D
Insert E
Evict A
```

LRU:

```text
A B C D
Access A
Access B
Insert E
Evict C
```

LRU attempts to keep the most valuable
translations in the cache.

## Phase 6 Insight

Cache size alone does not determine performance.

The replacement policy also matters.

Observed:

```text
FIFO Hit Rate = 20%

LRU Hit Rate  = 40%
```

LRU benefited from temporal locality and retained
translations that were still being actively used.

A smarter eviction policy can significantly
improve cache effectiveness.

## Phase 7 Insight

TLB performance depends on workload behavior.

Sequential Pattern:

```text
87.50% Hit Rate
```

Random Pattern:

```text
0.00% Hit Rate
```

The hardware remained unchanged.

Only the access pattern changed.

This demonstrates:

```text
Temporal Locality
```

Recently used translations are likely to be
used again.

Workloads with strong locality achieve higher
TLB hit rates and require fewer page walks.