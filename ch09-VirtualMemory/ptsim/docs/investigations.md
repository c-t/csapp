# Phase 0 - 48-bit Address Investigation

## Objective

Understand how x86-64 virtual addresses are
partitioned prior to page-table translation.

---

## Test Program

Observed:

```text
global : 0x5c7a519cb010
stack  : 0x7fff9b48d904
```

---

## Virtual Address Layout

x86-64 uses four page-table levels:

```text
| PML4 | PDPT | PD | PT | OFFSET |

   9      9     9    9      12
```

---

## Why 12 Offset Bits?

Standard page size:

```text
4096 bytes
```

Since:

```text
4096 = 2^12
```

the page offset occupies:

```text
12 bits
```

---

## Why 9-Bit Indices?

Each page-table level uses:

```text
9 bits
```

Therefore:

```text
2^9 = 512
```

entries can be stored in each table.

---

## Findings

A virtual address is not treated as a single
number during translation.

Instead it is interpreted as:

```text
PML4 Index
PDPT Index
PD Index
PT Index
Offset
```

Each field participates in the page-walk
process.

---

## Key Learning

AddrTx focused on:

```text
VPN + Offset
```

PTSim begins examining the internal structure
of the VPN itself.