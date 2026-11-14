# CallScope

Explore and visualize the System V AMD64 calling convention.

## Project Status

- [x] Phase 0 - ABI Investigation
- [x] Phase 1 - Argument Mapping
- [x] Phase 2 - Stack Argument Explorer
- [x] Phase 3 - ABI Visualizer
- [x] Phase 4 - Caller / Callee View
- [x] Phase 5 - Register Inspector
- [ ] Phase 6 - Struct & Pointer Arguments
- [ ] Phase 7 - Variadic Functions
- [ ] Phase 8 - Linux vs Windows ABI
---

## Implemented Features

### Phase 0 - ABI Investigation

Verified with GDB:

```text
arg1 -> RDI
arg2 -> RSI
arg3 -> RDX
arg4 -> RCX
arg5 -> R8
arg6 -> R9

arg7+ -> Stack
```

### Phase 1 - Argument Mapping

Mapped function arguments to their ABI locations.

```text
Arg1 -> RDI
Arg2 -> RSI
Arg3 -> RDX
Arg4 -> RCX
Arg5 -> R8
Arg6 -> R9
```

### Phase 2 - Stack Argument Explorer

Extended support to nine arguments.

```text
Arg7 -> STACK
Arg8 -> STACK
Arg9 -> STACK
```

### Phase 3 - ABI Visualizer

Visual representation of:

- Register arguments
- Stack arguments
- ABI layout
- Register exhaustion


### Phase 4 - Caller / Callee View

Visualized:

```text
Caller
   ↓
Register Loading
   ↓
Stack Preparation
   ↓
CALL
   ↓
Callee
```

Key Learning:

The caller is responsible for placing arguments into ABI-defined locations before transferring control to the callee.

### Phase 5 - Register Inspector

Implemented:

- Runtime register snapshot
- RDI inspection
- RSI inspection
- RDX inspection
- RCX inspection
- R8 inspection
- R9 inspection

Example:

Expected:

RDI = 1
RSI = 2
RDX = 3
RCX = 4
R8  = 5
R9  = 6

Observed:

RDI = 140723370537952
RSI = 2
RDX = 2
RCX = 4
R8  = 5
R9  = 6

Key Learning:

Argument registers are only guaranteed to contain
their argument values at function entry.

As execution proceeds, the compiler may reuse
registers for temporary values and other work.