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