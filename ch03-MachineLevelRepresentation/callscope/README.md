# CallScope

Explore and visualize the System V AMD64 calling convention.

---

## Project Status

- [x] Phase 0 - ABI Investigation
- [x] Phase 1 - Argument Mapping
- [x] Phase 2 - Stack Argument Explorer
- [x] Phase 3 - ABI Visualizer
- [x] Phase 4 - Caller / Callee View
- [x] Phase 5 - Register Inspector
- [x] Phase 6A - Pointer Arguments
- [x] Phase 6B - Small Struct Passing
- [x] Phase 6C - Large Struct Passing
- [x] Phase 7A - Variadic Function Register Analysis
- [ ] Phase 7B - Variadic Register-to-Stack Transition
- [ ] Phase 8 - Linux vs Windows ABI

---

## Key ABI Findings

### Integer Arguments

```text
Arg1 -> RDI
Arg2 -> RSI
Arg3 -> RDX
Arg4 -> RCX
Arg5 -> R8
Arg6 -> R9

Arg7+ -> Stack
```

### Pointer Arguments

Pointers are passed as addresses.

Example:

```c
foo(&value, &point);
```

```text
RDI -> &value
RSI -> &point
```

### Small Struct Passing

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
RDI = point.x
RSI = point.y
```

Small structs may be passed entirely through registers.

### Large Struct Passing

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
Stack copy before foo()
```

Large structs transition from register-based passing
to memory-based passing.

---

## Current ABI Classification

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

---

### Phase 7A - Variadic Function Register Analysis

Test:

```c
sum(5, 10, 20, 30, 40, 50);
```

Observed:

```text
RDI = 5

RSI = 10
RDX = 20
RCX = 30
R8  = 40
R9  = 50
```

Key Learning:

The fixed parameter consumes RDI.

Variadic arguments begin in the next available
argument register and continue following the
System V AMD64 ABI rules.