# ABI Comparison

## Purpose

This document summarizes the calling convention concepts
investigated throughout the CallScope project and
compares the Linux System V AMD64 ABI with the
Microsoft x64 ABI.

---

# System V AMD64 ABI

Used by:

- Linux
- BSD
- macOS

## Integer and Pointer Arguments

```text
Arg1 -> RDI
Arg2 -> RSI
Arg3 -> RDX
Arg4 -> RCX
Arg5 -> R8
Arg6 -> R9

Arg7+ -> Stack
```

---

# Microsoft x64 ABI

Used by:

- Windows

## Integer and Pointer Arguments

```text
Arg1 -> RCX
Arg2 -> RDX
Arg3 -> R8
Arg4 -> R9

Arg5+ -> Stack
```

---

# Register Comparison

| Argument | Linux | Windows |
|-----------|--------|----------|
| Arg1 | RDI | RCX |
| Arg2 | RSI | RDX |
| Arg3 | RDX | R8 |
| Arg4 | RCX | R9 |
| Arg5 | R8 | Stack |
| Arg6 | R9 | Stack |

---

# Stack Usage

## Linux

```text
Registers available : 6
Stack begins at     : Arg7
```

## Windows

```text
Registers available : 4
Stack begins at     : Arg5
```

---

# Shadow Space

## Linux

```text
No shadow space requirement
```

## Windows

```text
Caller allocates
32-byte shadow space
before every call
```

---

# CallScope Findings

## Integer Arguments

Observed:

```text
Arg1 -> RDI
Arg2 -> RSI
Arg3 -> RDX
Arg4 -> RCX
Arg5 -> R8
Arg6 -> R9
```

Conclusion:

Integer arguments are passed through
general-purpose argument registers.

---

## Pointer Arguments

Observed:

```text
RDI = &value
RSI = &point
```

Conclusion:

Pointers are passed as addresses.

---

## Small Structs

Test:

```c
typedef struct
{
    long x;
    long y;
} point_t;
```

Observed:

```text
RDI = 10
RSI = 20
```

Conclusion:

Small structs may be fully passed
through registers.

---

## Large Structs

Test:

```c
typedef struct
{
    long a;
    long b;
    long c;
    long d;
    long e;
} big_t;
```

Observed:

```text
Temporary stack copy
before function call
```

Conclusion:

Large structs transition to
memory-based passing.

---

## Variadic Functions

Observed:

```text
RDI = count

RSI = arg1
RDX = arg2
RCX = arg3
R8  = arg4
R9  = arg5
```

Additional arguments:

```text
Stack
```

Conclusion:

Variadic arguments seamlessly transition
from register-backed storage to stack-backed
storage.

---

# Final ABI Classification

```text
Integer
    -> Register

Pointer
    -> Register

Small Struct
    -> Registers

Large Struct
    -> Memory / Stack

Variadic Arguments
    -> Registers
    -> Stack
```

---

# Key Takeaways

1. Function arguments are not immediately stack-based.
2. Registers are the first transport mechanism.
3. Pointers are just addresses passed in registers.
4. Small structs may be decomposed into registers.
5. Large structs eventually transition to memory.
6. Variadic functions use ABI bookkeeping to consume both register and stack arguments.
7. Linux and Windows use different calling conventions and stack layouts.

---

# CallScope Conclusion

CallScope explored:

- Argument mapping
- Stack argument passing
- Caller/callee interaction
- Register inspection
- Pointer passing
- Struct classification
- Variadic functions
- Cross-platform ABI differences

The project demonstrates how high-level C function calls are transformed into low-level machine-level ABI operations.