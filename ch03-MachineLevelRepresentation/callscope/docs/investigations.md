# Phase 0 Investigation

Test:

```c
foo(1,2,3,4,5,6,7);
```

Observed in GDB:

```text
rdi = 1
rsi = 2
rdx = 3
rcx = 4
r8  = 5
r9  = 6
```

Conclusion:

```text
arg1 -> RDI
arg2 -> RSI
arg3 -> RDX
arg4 -> RCX
arg5 -> R8
arg6 -> R9
```

Additional arguments are stack-passed.

Observed:

```text
arg7 = 7
```

on stack.

Compiler:

```bash
gcc -O0 -g -fno-omit-frame-pointer
```

Observation:

Register arguments are often spilled to memory at -O0 to support debugging.

---

# Phase 2 Investigation

Test:

```c
foo(
 1,2,3,
 4,5,6,
 7,8,9
);
```

Result:

```text
Registers

1 2 3 4 5 6

Stack

7 8 9
```

Conclusion:

System V AMD64 supports six integer/pointer arguments in registers.

Additional arguments are passed via stack memory.

---

# Phase 3 Investigation

Created ABI visualizer.

Visualized:

```text
Register File
```

and

```text
Stack Layout
```

for a 9-argument function call.

Key Learning:

```text
Arguments do not immediately go to the stack.

The ABI first uses:

RDI
RSI
RDX
RCX
R8
R9

before spilling additional arguments to the stack.
```
# Phase 5 Investigation

Objective

Capture live register values during execution.

Expected

RDI = 1
RSI = 2
RDX = 3
RCX = 4
R8  = 5
R9  = 6

Observed

RDI = 140723370537952
RSI = 2
RDX = 2
RCX = 4
R8  = 5
R9  = 6

Analysis

Some registers matched the expected ABI mapping.

Some registers did not.

This indicates that by the time the snapshot
was taken, the compiler had already reused
certain registers.

Conclusion

The System V ABI guarantees argument placement
at function entry.

It does not guarantee that registers continue
to hold those values throughout execution.

Key Learning

ABI rules describe how arguments arrive.

Runtime inspection reveals how registers evolve
after execution begins.

# Phase 6A - Pointer Arguments

Test:

```c
foo(&value, &point);
```

Observed:

```text
RDI = 0x7fffffffd64c
RSI = 0x7fffffffd650
```

Function Parameters:

```text
value = 0x7fffffffd64c
point = 0x7fffffffd650
```

Conclusion:

Pointer arguments are passed through the same
argument registers used for integer values.

The register contains the address of the object.

Memory Verification:

```text
point.x = 10
point.y = 20
```

confirmed via:

```gdb
x/2wx $rsi
```

# Phase 6A - Pointer Arguments

Test:

```c
foo(&value, &point);
```

Observed:

```text
value = 0x7fffffffd64c
point = 0x7fffffffd650

RDI = 0x7fffffffd64c
RSI = 0x7fffffffd650
```

Conclusion:

Pointer arguments are passed through
the same argument registers used for integers.

The register contains the address of the object.

---

# Phase 6B - Small Struct Passing

Struct:

```c
typedef struct
{
    long x;
    long y;
} point_t;
```

Size:

```text
16 bytes
```

Observed:

```text
point = {x = 10, y = 20}

RDI = 10
RSI = 20
```

Conclusion:

The structure was decomposed into fields.

Each field was passed through a register.

No pointer was involved.

No stack memory was required.

---

# Phase 6C - Large Struct Passing

Struct:

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

Size:

```text
40 bytes
```

Observed:

```text
value = {10,20,30,40,50}
```

Disassembly:

```asm
sub $0x28,%rsp

mov field a
mov field b
mov field c
mov field d
mov field e

call foo
```

Interpretation:

The compiler allocated temporary stack space.

The structure was copied into that memory.

The function was then invoked.

Conclusion:

Large structures transition from:

```text
Register Passing
```

to:

```text
Memory-Based Passing
```

---

# Summary

Current System V AMD64 Findings

```text
Integer
    -> Register

Pointer
    -> Register

Small Struct
    -> Registers

Large Struct
    -> Stack / Memory
```

Key Learning:

Pass-by-value does not automatically imply
stack-based argument passing.

The ABI classifies arguments and selects the
most efficient transport mechanism.

---

# Phase 7A - Variadic Function Register Analysis

Test

```c
sum(5, 10, 20, 30, 40, 50);
```

Observed

```text
RDI = 5
RSI = 10
RDX = 20
RCX = 30
R8  = 40
R9  = 50
```

Interpretation

Fixed Argument

count -> RDI

Variadic Arguments

10 -> RSI
20 -> RDX
30 -> RCX
40 -> R8
50 -> R9

Conclusion

The fixed parameter consumes the first ABI
argument register.

Variadic arguments then occupy the remaining
registers according to the standard System V
AMD64 calling convention.

# Phase 8 - ABI Comparison

System V AMD64

```text
Arg1 -> RDI
Arg2 -> RSI
Arg3 -> RDX
Arg4 -> RCX
Arg5 -> R8
Arg6 -> R9

Arg7+ -> Stack
```

Microsoft x64

```text
Arg1 -> RCX
Arg2 -> RDX
Arg3 -> R8
Arg4 -> R9

Arg5+ -> Stack
```

Windows shadow space:

```text
32 bytes
```

Linux shadow space:

```text
None
```

Conclusion

Both ABIs solve the same problem but use
different register layouts and stack conventions.

# Final Project Findings

Argument Classification

Integer
    -> Register

Pointer
    -> Register

Small Struct
    -> Registers

Large Struct
    -> Stack / Memory

Variadic Arguments
    -> Registers
    -> Stack