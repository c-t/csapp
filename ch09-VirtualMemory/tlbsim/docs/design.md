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
