# Notes

## Phase 0 Insight

A virtual address contains enough information
to locate page-table entries at each level of
the translation hierarchy.

---

## Address Structure

```text
| PML4 | PDPT | PD | PT | OFFSET |
```

---

## Offset

```text
12 bits
```

correspond to the byte position within a page.

---

## Page-Table Levels

Each level receives:

```text
9 bits
```

which select one of:

```text
512 entries
```

within the table.

---

## Connection To AddrTx

AddrTx taught:

```text
Virtual Address
      ↓
VPN + Offset
```

PTSim will explore:

```text
VPN
 ↓
PML4
 ↓
PDPT
 ↓
PD
 ↓
PT
```

during a simulated page walk.