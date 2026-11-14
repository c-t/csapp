# CallScope Design

Goal:

Understand and visualize the System V AMD64 calling convention.

## Roadmap

### Phase 0 - ABI Investigation ✅

Validate ABI behavior using:

- objdump
- gdb
- register inspection

### Phase 1 - Argument Mapping ✅

Map arguments to ABI locations.

```text
Arg1 -> RDI
Arg2 -> RSI
Arg3 -> RDX
Arg4 -> RCX
Arg5 -> R8
Arg6 -> R9
```

### Phase 2 - Stack Argument Explorer ✅

Explore arguments beyond six.

```text
Arg7+
    ↓
Stack
```

### Phase 3 - ABI Visualizer ✅

Visual representation of:

- Register file
- Stack arguments
- Register exhaustion

### Phase 4 - Caller/Callee View

Visualize:

```text
Caller
   ↓
Registers
   ↓
Call Instruction
   ↓
Callee
```

### Phase 5 - Register Inspector

Capture actual register values at function entry.

### Phase 6 - Struct & Pointer Arguments

Study:

- structures
- pointers
- passing by reference

### Phase 7 - Variadic Functions

Study:

```c
printf(...)
```

and variadic ABI behavior.

### Phase 8 - Linux vs Windows ABI

Compare:

System V AMD64

vs

Microsoft x64 ABI.