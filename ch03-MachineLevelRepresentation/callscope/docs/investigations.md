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