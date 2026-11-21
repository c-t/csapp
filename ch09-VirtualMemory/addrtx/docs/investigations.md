# AddrTx Investigations

## Virtual Address Structure

Observed:

```text
Virtual Address
    =
VPN + Offset
```

Example:

```text
0x62911491e010

VPN    = 0x62911491e
Offset = 0x10
```

---

## Binary Representation

Addresses can be visualized as:

```text
| VPN | OFFSET |
```

The offset occupies the lower bits while the VPN
occupies the upper bits.

---

## Page Size Analysis

Investigated:

```text
4 KB
2 MB
1 GB
```

pages.

Finding:

```text
Larger Page Size
        ↓
More Offset Bits
        ↓
Fewer VPN Bits
```

Large pages reduce translation overhead.

---

## Shared Pages

Observed:

```text
0x7fffb7d9c290
0x7fffb7d9c28c
```

Both produced:

```text
VPN = 0x7fffb7d9c
```

Finding:

```text
Different addresses can share
the same virtual page.
```

---

## Linux Process Memory Regions

Using:

```text
/proc/self/maps
```

identified:

```text
Executable Mapping
Heap Mapping
Stack Mapping
```

Examples:

```text
[heap]

[stack]

/home/.../build/addrtx
```

---

## Process-Specific Addresses

Addresses collected from one process could not
be resolved in another process.

Finding:

```text
Virtual addresses are process-specific.
```

The same numerical address value does not imply
the same memory location across processes.

---

## Translation Statistics

Runtime Dataset:

```text
Addresses     : 4
Unique VPNs   : 3
Shared Pages  : 1
Utilization   : 75%
```

Finding:

```text
Translation cost depends on
unique pages rather than
address count.
```

---

## Final Result

AddrTx demonstrates:

```text
Address
   ↓
Page
   ↓
Memory Region
   ↓
Process Address Space
```

using actual Linux process memory mappings.