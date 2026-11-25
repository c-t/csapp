# Phase 0 - TLB Investigation

## Objective

Understand the role of the Translation Lookaside
Buffer in virtual memory translation.

---

## Observation

PTSim demonstrated:

Virtual Address
↓
Page Walk
↓
Physical Frame

However, performing a page walk for every memory
access would be expensive.

---

## TLB Concept

The processor maintains a cache of recent
translations.

Structure:

VPN
↓
Frame

---

## Hit

If the VPN exists in the TLB:

VPN
↓
TLB
↓
Frame

No page walk is required.

---

## Miss

If the VPN does not exist in the TLB:

VPN
↓
TLB MISS
↓
Page Walk
↓
Frame
↓
Insert Into TLB

---

## Key Learning

The TLB exists to avoid repeated page walks for
recently translated virtual pages.

# Phase 1 - TLB Entry Structures

## Example Entries

```text
Entry 0

VPN   = 0x7ffff84e3

Frame = 0x10e3
```

```text
Entry 1

VPN   = 0x58dc74280

Frame = 0x1080
```

## Observations

Only a small number of entries are populated.

Remaining entries remain invalid:

```text
Valid = no
```

which reflects an initially empty cache.

## Findings

A TLB entry stores:

- VPN
- Physical Frame
- Valid Bit

## Key Learning

The TLB is a cache of translation results rather
than a cache of memory contents.

# Phase 2 - TLB Lookup

## Cached Translation

```text
VPN   = 0x7ffff84e3

Frame = 0x10e3
```

Lookup Result:

```text
HIT
```

---

## Absent Translation

```text
VPN = 0x12345678
```

Lookup Result:

```text
MISS
```

---

## Findings

A valid VPN lookup returns a previously cached
frame.

If the VPN is not present, the lookup fails and a
page walk becomes necessary.

## Key Learning

TLB lookups are the first stage of modern virtual
memory translation.

# Phase 3 - TLB Fill

## Initial Lookup

```text
VPN : 0x12345678

Result : MISS
```

---

## Simulated Page Walk

```text
VPN   : 0x12345678

Frame : 0x1678
```

---

## Insert Into TLB

```text
VPN   : 0x12345678

Frame : 0x1678
```

---

## Second Lookup

```text
VPN : 0x12345678

Result : HIT

Frame : 0x1678
```

---

## Findings

A TLB miss triggers translation.

The resulting frame is inserted into the TLB.

Subsequent lookups avoid repeating the page
walk.

## Key Learning

TLBs exploit translation reuse by caching
successful page-walk results.

# Phase 4 - Repeated Accesses

## Test Pattern

```text
VPN A
VPN B
VPN A
VPN A
VPN B
```

## Results

```text
0xaaa -> MISS -> Frame 0x1aaa

0xbbb -> MISS -> Frame 0x1bbb

0xaaa -> HIT  -> Frame 0x1aaa

0xaaa -> HIT  -> Frame 0x1aaa

0xbbb -> HIT  -> Frame 0x1bbb
```

## Statistics

```text
Total Accesses : 5

Hits           : 3

Misses         : 2

Hit Rate       : 60.00%

Miss Rate      : 40.00%
```

## Findings

The first access to a VPN requires translation.

Subsequent accesses reuse the cached TLB entry.

Only two page walks were required for five
virtual page references.

## Key Learning

TLBs exploit temporal locality.

Recently used translations are likely to be
used again and therefore benefit from caching.

# Phase 5 - Replacement Policies

## FIFO Experiment

Capacity:

```text
4 Entries
```

Insert Sequence:

```text
AAA
BBB
CCC
DDD
EEE
```

Result:

```text
Evict AAA
```

Final State:

```text
EEE
BBB
CCC
DDD
```

### Observation

FIFO removes entries based solely on insertion
order.

Recent usage is ignored.

---

## LRU Experiment

Insert:

```text
AAA
BBB
CCC
DDD
```

Access:

```text
AAA
AAA
BBB
```

Insert:

```text
EEE
```

Result:

```text
Evict CCC
```

Final State:

```text
AAA
BBB
EEE
DDD
```

### Observation

LRU preserved recently used translations.

The least recently used entry was selected as
the victim.

---

## Findings

FIFO and LRU may produce different eviction
decisions for the same workload.

LRU generally retains translations that are
actively reused.

---

## Key Learning

A cache is not merely a storage structure.

A cache must also decide:

```text
What stays?
What goes?
```

Replacement policy answers that question.

# Phase 6 - Translation Statistics

## Workload

```text
AAA
BBB
CCC
DDD
AAA
BBB
EEE
AAA
BBB
FFF
```

## FIFO Results

```text
Accesses  : 10
Hits      : 2
Misses    : 8

Hit Rate  : 20%
```

## LRU Results

```text
Accesses  : 10
Hits      : 4
Misses    : 6

Hit Rate  : 40%
```

## Findings

LRU achieved twice the hit rate of FIFO for the
same workload.

FIFO removed translations based solely on age.

LRU retained recently reused translations.

## Key Learning

Replacement policy strongly influences cache
performance even when cache capacity remains
unchanged.

# Phase 7 - Locality Experiments

## Sequential Workload

Pattern

```text
AAA
AAA
AAA
AAA
AAA
AAA
AAA
AAA
```

Results

```text
Accesses : 8

Hits     : 7

Misses   : 1

Hit Rate : 87.50%

Miss Rate: 12.50%
```

### Observation

Only the first access required a page walk.

All subsequent accesses reused the cached TLB
entry.

---

## Random Workload

Pattern

```text
AAA
BBB
CCC
DDD
EEE
FFF
111
222
```

Results

```text
Accesses : 8

Hits     : 0

Misses   : 8

Hit Rate : 0.00%

Miss Rate: 100.00%
```

### Observation

Each VPN was unique.

No cached translation was reused.

---

## Comparison

```text
Sequential Hit Rate : 87.50%

Random Hit Rate     : 0.00%
```

## Findings

The same TLB produced dramatically different
performance depending on the workload.

Sequential workloads benefit from translation
reuse.

Random workloads provide little opportunity for
reuse.

## Key Learning

Locality is one of the primary reasons TLBs are
effective in real systems.

# Final Findings

## TLB Purpose

Cache recent VPN-to-frame translations.

## Cache Behavior

```text
Lookup
Hit
Miss
Fill
Evict
```

## Replacement Policies

FIFO:

```text
Oldest Entry
```

LRU:

```text
Least Recently Used Entry
```

## Locality

Sequential workloads:

```text
High Hit Rate
```

Random workloads:

```text
Low Hit Rate
```

## Conclusion

TLB performance depends on:

- Translation reuse
- Replacement policy
- Workload locality
```