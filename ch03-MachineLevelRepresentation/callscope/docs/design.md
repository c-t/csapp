# CallScope Design

Goal:

Understand and visualize the System V AMD64 ABI.

---

## Roadmap

### Phase 0 - ABI Investigation ✅

Validate ABI behavior using:

- GDB
- objdump
- register inspection

### Phase 1 - Argument Mapping ✅

Map arguments to ABI locations.

### Phase 2 - Stack Argument Explorer ✅

Visualize arguments beyond six.

```text
Arg7+
    ↓
Stack
```

### Phase 3 - ABI Visualizer ✅

Visual representation of:

- Register arguments
- Stack arguments
- Register exhaustion

### Phase 4 - Caller / Callee View ✅

Visualize:

```text
Caller
    ↓
Register Setup
    ↓
CALL
    ↓
Callee
```

### Phase 5 - Register Inspector ✅

Capture runtime register values.

Learning Objective:

```text
ABI Specification
       vs
Actual Register State
```

### Phase 6A - Pointer Arguments ✅

Investigate address passing.

### Phase 6B - Small Struct Passing ✅

Investigate register-based aggregate passing.

### Phase 6C - Large Struct Passing ✅

Investigate memory-based aggregate passing.

### Phase 7 - Variadic Functions

Study:

```c
printf(...)
```

Topics:

- va_list
- va_start
- va_arg
- va_end

### Phase 8 - Linux vs Windows ABI

Compare:

System V AMD64 ABI

vs

Microsoft x64 ABI

---

## Argument Classification Model

```text
Integer
    ↓
Register

Pointer
    ↓
Register

Small Struct
    ↓
Registers

Large Struct
    ↓
Memory
```
### Phase 7A - Variadic Register Layout ✅

Function:

```c
void sum(int count, ...)
```

Learning Objective:

Understand how variable-length argument lists
interact with the ABI.

Observed Layout:

```text
count -> RDI

arg1 -> RSI
arg2 -> RDX
arg3 -> RCX
arg4 -> R8
arg5 -> R9
```

Next:

Investigate ABI behavior when variadic arguments
exceed available registers.