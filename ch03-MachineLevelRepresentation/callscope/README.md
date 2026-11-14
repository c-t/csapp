# CallScope

Explore and visualize the System V AMD64 calling convention.

## Project Status

- [x] Phase 0 - ABI Investigation
- [x] Phase 1 - Argument Mapping
- [x] Phase 2 - Stack Argument Explorer
- [x] Phase 3 - ABI Visualizer
- [ ] Phase 4 - Caller/Callee View
- [ ] Phase 5 - Register Inspector
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

---

## Next Phase

Phase 4 – Caller/Callee View

Visualize argument movement from caller to callee.