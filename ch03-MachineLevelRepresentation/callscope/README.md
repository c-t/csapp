# CallScope

Explore and visualize the System V AMD64 calling convention.

## Project Status

- [x] Phase 0 - ABI Investigation
- [x] Phase 1 - Argument Mapping
- [x] Phase 2 - Stack Argument Explorer
- [ ] Phase 3 - ABI Visualizer
- [ ] Phase 4 - Caller/Callee View
- [ ] Phase 5 - Register Inspector
- [ ] Phase 6 - Struct & Pointer Arguments
- [ ] Phase 7 - Variadic Functions
- [ ] Phase 8 - Linux vs Windows ABI

---

## Completed Findings

### Phase 0 - ABI Investigation

Verified using GDB:

```text
arg1 -> RDI
arg2 -> RSI
arg3 -> RDX
arg4 -> RCX
arg5 -> R8
arg6 -> R9

arg7+ -> Stack
```

Observed:

```text
RDI = 1
RSI = 2
RDX = 3
RCX = 4
R8  = 5
R9  = 6
```

Compiler:

```bash
gcc -O0 -g -fno-omit-frame-pointer
```

Observation:

Register arguments are often spilled to stack locations at `-O0` for debugging support.

---

### Phase 1 - Argument Mapping

Implemented ABI argument mapping:

```text
Arg1 -> RDI
Arg2 -> RSI
Arg3 -> RDX
Arg4 -> RCX
Arg5 -> R8
Arg6 -> R9
```

Goal:

Understand how arguments are assigned to registers under the System V AMD64 ABI.

---

### Phase 2 - Stack Argument Explorer

Extended test cases beyond six arguments.

Example:

```c
foo(1,2,3,4,5,6,7,8,9);
```

Output:

```text
Register Arguments

Arg1 -> RDI : 1
Arg2 -> RSI : 2
Arg3 -> RDX : 3
Arg4 -> RCX : 4
Arg5 -> R8  : 5
Arg6 -> R9  : 6

Stack Arguments

Arg7 -> STACK : 7
Arg8 -> STACK : 8
Arg9 -> STACK : 9
```

Key Learning:

The first six integer/pointer 