# StackViz

StackViz is a small runtime stack visualizer built while studying the x86-64 stack discipline discussed in Computer Systems: A Programmer's Perspective (CSAPP).

It helps inspect:
- the current frame (`RSP`, `RBP`, saved `RBP`, return address)
- raw stack memory
- the call-frame chain
- a simple recursion tree
- function symbol names and backtraces
- local variables by explicit stack offset metadata
- source-file and line mapping for call sites

## Build

From this directory:

```bash
gcc -D_GNU_SOURCE -Wall -Wextra -Werror -std=c17 -O0 -g -fno-omit-frame-pointer \
  -Iinclude tests/test_simple.c src/stackviz.c -o test_simple -ldl -rdynamic
```

## Run

```bash
./test_simple
```

## Included examples

- `tests/test_simple.c` — basic function frame and local-variable dump
- `tests/test_recursion.c` — recursion visualization with repeated nested calls

## Current status

This project implements the core runtime stack investigation flow:
- frame inspection
- raw stack memory dump
- ASCII frame layout
- frame chain walk
- backtrace with symbol names
- recursion visualization
- local variable discovery with metadata
- source mapping via `addr2line`

This is still an educational project and not a full DWARF debugger or general-purpose unwinder.

## Verified project scope

The current implementation has been validated on x86-64 Linux with GCC and covers the core runtime stack analysis workflow:
- frame traversal and saved-RBP / return-address inspection
- raw stack memory dumps
- recursion visualization
- symbol name resolution via `dladdr`
- source-file and line mapping through `addr2line`
- local-variable discovery by explicit stack-offset metadata

The project is complete for the learning objectives it set out to explore.
