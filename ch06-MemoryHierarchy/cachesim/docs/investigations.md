# Phase 0 - Cache Investigation

## Objective

Understand cache organization and cache
addressing.

---

## Observation

A cache cannot store every memory location.

Memory addresses must therefore be mapped to
specific cache locations.

---

## Cache Components

### Cache Line

Stores a block of memory.

### Cache Set

A collection of cache lines.

### Cache Tag

Identifies which memory block occupies a cache
line.

### Block Offset

Selects a byte within a cache block.

---

## Address Breakdown

```text
+------+-----------+--------+
| Tag  | Set Index | Offset |
+------+-----------+--------+
```

---

## Cache Lookup

```text
Address
   ↓
Set Index
   ↓
Select Set
   ↓
Tag Compare

Hit?
 ↓

Data

Miss?
 ↓

Memory Fetch
```

---

## Key Learning

Cache behavior begins with address
decomposition.

Every cache lookup depends on:

```text
Tag
Set Index
Offset
```

## Phase 1 - Address Decomposition ✅

Goal

Decompose a memory address into the fields used
during cache lookup.

Address Format

```text
+----------------------+----------+--------+
|         Tag          |   Set    | Offset |
+----------------------+----------+--------+

        22               6          4
```

Field Purpose

Tag:

```text
Identifies a memory block.
```

Set Index:

```text
Selects a cache set.
```

Block Offset:

```text
Selects a byte within a cache block.
```

Learning Objective

Understand how memory addresses are interpreted
by a cache before any lookup occurs.

# Phase 2 - Cache Structures

## Cache Configuration

```text
Cache Size  : 1024 Bytes

Block Size  : 16 Bytes

Cache Lines : 64
```

## Organization

```text
64 Sets

1 Line Per Set

Direct Mapped
```

## Initial State

All cache lines are initialized as:

```text
Tag   = 0

Valid = 0
```

Example:

```text
Set 39

Tag   = 0

Valid = no
```

## Findings

Each set contains one cache line.

The valid bit determines whether the cache line
contains meaningful data.

## Key Learning

Cache structures provide the storage that will
later support cache hits and misses.