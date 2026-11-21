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