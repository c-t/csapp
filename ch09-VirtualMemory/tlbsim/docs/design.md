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