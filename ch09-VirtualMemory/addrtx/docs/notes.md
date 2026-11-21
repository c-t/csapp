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