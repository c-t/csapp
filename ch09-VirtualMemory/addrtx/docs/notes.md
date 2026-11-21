# Notes

## VPN + Offset

A virtual address consists of:

```text
Virtual Page Number
        +
Page Offset
```

---

## Page Translation

Translation operates on:

```text
VPN
```

The offset passes through unchanged.

---

## Shared Pages

Addresses with the same VPN reside in:

```text
The Same Virtual Page
```

and therefore share:

```text
Page Translation
Page Table Entry
TLB Entry
```

---

## Huge Pages

Increasing page size:

```text
4 KB
→
2 MB
→
1 GB
```

results in:

```text
More Offset Bits
Fewer VPN Bits
Fewer Pages
```

---

## Process Isolation

A virtual address is meaningful only within the
process that owns the address space.

```text
Same Address Value
        ≠
Same Memory
```

across processes.

---

## Linux Memory Layout

Linux exposes process mappings through:

```text
/ proc / self / maps
```

including:

- Executable
- Heap
- Stack
- Anonymous Regions

---

## AddrTx v1.0 Summary

AddrTx provides a practical introduction to:

- Virtual Addresses
- Paging
- Virtual Page Numbers
- Linux Memory Layout
- Page Sharing
- Translation Analysis

and serves as a foundation for:

```text
Multi-Level Page Table Simulator
TLB Simulator
Demand Paging Simulator
```