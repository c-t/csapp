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