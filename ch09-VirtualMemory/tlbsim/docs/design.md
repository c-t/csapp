# TLBSim Design

## Objective

Build a Translation Lookaside Buffer simulator
that demonstrates how processors cache virtual
to physical address translations.

---

## Problem

Without a TLB:

VPN
↓
Page Walk
↓
Frame

Every memory access would require a page walk.

---

## Solution

TLB

VPN
↓
TLB Lookup

Hit?
↓
Frame

Miss?
↓
Page Walk
↓
Frame

---

## Roadmap

Phase 0 - TLB Investigation ✅

Phase 1 - TLB Entry Structures

Phase 2 - TLB Lookup

Phase 3 - TLB Fill

Phase 4 - Repeated Accesses

Phase 5 - Replacement Policies

Phase 6 - Translation Statistics

Phase 7 - Locality Experiments

Phase 8 - TLBSim v1.0

## Phase 1 - TLB Entry Structures ✅

Goal

Create a fixed-size TLB capable of storing cached
translations.

Structure

```text
VPN
Frame
Valid Bit
```

Implementation

```c
typedef struct
{
    uint64_t vpn;
    uint64_t frame;
    int valid;
} tlb_entry_t;
```

Learning Objective

Understand the information stored by a TLB and
how it represents cached page-walk results.

## Phase 2 - TLB Lookup ✅

Goal

Search the TLB for a VPN and determine whether a
cached translation exists.

Implementation

```text
VPN
 ↓
Search TLB
```

Results

```text
HIT
```

or

```text
MISS
```

Learning Objective

Understand how processors determine whether a
page walk is required.

## Phase 3 - TLB Fill ✅

Goal

Handle TLB misses by performing translation and
inserting the result into the TLB.

Flow

```text
VPN
 ↓
MISS
 ↓
Page Walk
 ↓
Frame
 ↓
Insert Into TLB
```

Learning Objective

Understand how processors populate the TLB
after discovering a translation.

## Phase 4 - Repeated Accesses ✅

Goal

Demonstrate how cached translations reduce
future page walks.

Method

Simulate repeated VPN references:

```text
A
B
A
A
B
```

Expected Behavior

```text
MISS
MISS
HIT
HIT
HIT
```

Measurements

```text
Hits
Misses
Hit Rate
Miss Rate
```

Learning Objective

Demonstrate temporal locality and the value of
translation caching.

## Phase 5 - Replacement Policies ✅

Goal

Demonstrate how finite-capacity TLBs manage
cached translations.

### FIFO

Victim Selection:

```text
Oldest Inserted Entry
```

### LRU

Victim Selection:

```text
Least Recently Used Entry
```

Implementation

Each TLB entry tracks:

```text
VPN
Frame
Valid Bit
```

LRU additionally tracks:

```text
Last Used Timestamp
```

Learning Objective

Understand how cache replacement policies affect
which translations remain available.