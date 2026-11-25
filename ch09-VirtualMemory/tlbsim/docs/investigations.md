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