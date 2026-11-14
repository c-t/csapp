# CallScope

Explore the System V AMD64 calling convention.

## Project Status

- [x] Phase 0 - ABI Investigation
- [x] Phase 1 - Argument Mapping
- [ ] Phase 2 - Stack Argument Explorer
- [ ] Phase 3 - ABI Visualizer
- [ ] Phase 4 - Caller/Callee View
- [ ] Phase 5 - Register Inspector
- [ ] Phase 6 - Struct & Pointer Arguments
- [ ] Phase 7 - Variadic Functions
- [ ] Phase 8 - Linux vs Windows ABI

## Completed Findings

### Phase 0

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

### Phase 1

Implemented argument-to-register ABI mapping view.

## Next Phase

Phase 2 – Stack Argument Explorer
