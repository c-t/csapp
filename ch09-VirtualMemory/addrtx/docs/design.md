# AddrTx Design

## Objective

Build a virtual memory exploration tool that progressively
reveals how virtual addresses are interpreted by hardware
and operating systems.

---

## Architecture

```text
Virtual Address
        |
        v

+----------------+
| VPN + Offset   |
+----------------+
        |
        v

+----------------+
| Binary Layout  |
+----------------+
        |
        v

+----------------+
| Classification |
+----------------+
        |
        v

+----------------+
| Page Analysis  |
+----------------+
        |
        v

+----------------+
| Region Lookup  |
+----------------+
        |
        v

+----------------+
| Statistics     |
+----------------+
```

---

## Components

### translator.c

Extracts:

```text
VPN
Offset
```

from virtual addresses.

---

### formatter.c

Provides formatted output and binary visualizations.

---

### classifier.c

Performs heuristic virtual memory classification.

---

### page_sizes.c

Analyzes address translation across:

```text
4 KB pages
2 MB pages
1 GB pages
```

---

### maps.c

Parses:

```text
/proc/self/maps
```

and resolves addresses to actual Linux memory regions.

---

### multi_address.c

Compares addresses and identifies:

```text
Shared VPNs
Shared Pages
```

---

### stats.c

Calculates:

- Translation counts
- Unique pages
- Shared page metrics

---

### runtime.c

Constructs a runtime dataset using:

```text
Global Variables
Heap Objects
Stack Variables
```

from the executing process.

---

## Design Principles

- Investigation-first learning
- Small focused phases
- Observable system behavior
- Linux-first implementation
- Minimal dependencies