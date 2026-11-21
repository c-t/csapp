# Notes

## Phase 2 Insight

Addresses should no longer be viewed as a
single hexadecimal value.

Instead:

```text
Address
    =
VPN + Offset
```

Example:

```text
0x600e0c861010

VPN    = 0x600e0c861
Offset = 0x10
```

Equivalent View:

```text
Page Base
    +
Byte Offset
```

```text
0x600e0c861000
+
0x10
=
0x600e0c861010
```

## Phase 3 Insight

The same VPN implies:

```text
Same Virtual Page
```

Example:

```text
heap ptr VPN = 0x7ffc007b9
stack VPN    = 0x7ffc007b9
```

Even though these are different variables,
they share the same page and therefore
the same page translation.

## Phase 4 Insight

A virtual address is interpreted differently
depending on page size.

Example:

```text
4 KB Page
    ↓
VPN + 12-bit Offset

2 MB Page
    ↓
VPN + 21-bit Offset

1 GB Page
    ↓
VPN + 30-bit Offset
```

Larger pages result in fewer virtual pages
covering the same memory range.

## Phase 5 Insight

Two addresses can appear unrelated:

```text
0x7fff4ca70d90
0x7fff4ca70d8c
```

Yet belong to the same page:

```text
VPN = 0x7fff4ca70
```

This means page translation depends on the
VPN and not the offset.

The offset merely identifies a location
within the page.

## Phase 6 Insight

A virtual address consists of more than:

```text
VPN + Offset
```

It also exists within:

```text
A Process Address Space
```

Example:

```text
0x5d9499148010
```

obtained from:

```text
test_basic
```

could not be resolved inside:

```text
AddrTx
```

because the address belonged to a different
process.

Important:

```text
Same Address Value
        ≠
Same Memory
```

across different processes.

Linux exposes process memory layout through:

```text
/ proc / self / maps
```

which describes the current process address
space.

## Phase 7 Insight

Four addresses did not require four page
translations.

Observed:

```text
Addresses   : 4
Unique VPNs : 3
```

Two addresses shared the same virtual page and
therefore the same translation.

This is the same principle exploited by:

- TLBs
- Page Tables
- Huge Pages
