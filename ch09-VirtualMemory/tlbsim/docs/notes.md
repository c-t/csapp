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