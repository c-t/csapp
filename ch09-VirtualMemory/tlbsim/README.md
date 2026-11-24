# TLBSim

Translation Lookaside Buffer Simulator

TLBSim is a Chapter 9 (Virtual Memory) learning
project inspired by CS:APP.

The project explores how processors avoid
performing expensive page walks for every memory
access by caching translations in a Translation
Lookaside Buffer (TLB).

---

## Overview

PTSim answered:

Virtual Address
↓
Page Walk
↓
Frame

TLBSim answers:

Virtual Address
↓
VPN
↓
TLB

Hit?
↓
Frame

Miss?
↓
Page Walk
↓
Frame

---

## Project Status

- [x] Phase 0 - TLB Investigation
- [ ] Phase 1 - TLB Entry Structures
- [ ] Phase 2 - TLB Lookup
- [ ] Phase 3 - TLB Fill
- [ ] Phase 4 - Repeated Accesses
- [ ] Phase 5 - Replacement Policies
- [ ] Phase 6 - Translation Statistics
- [ ] Phase 7 - Locality Experiments
- [ ] Phase 8 - TLBSim v1.0
