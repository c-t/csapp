# CSAPP Learning Repository

This repository is a hands-on learning workspace for Computer Systems: A Programmer's Perspective (CSAPP). It contains experiments, notes, small programs, and implementation-focused projects for understanding how software interacts with hardware, memory, and the operating system at a low level.

## Focus areas

- machine-level representation
- assembly and compiler behavior
- stack frames and calling conventions
- memory layout and pointer arithmetic
- recursion and function-call analysis
- ELF and binary structure
- debugging and runtime inspection
- Linux system programming concepts

## Featured projects

- [ch03-MachineLevelRepresentation/stackviz](ch03-MachineLevelRepresentation/stackviz) — runtime stack inspection, frame analysis, recursion tracing, and source-location mapping
- [ch03-MachineLevelRepresentation/callscope](ch03-MachineLevelRepresentation/callscope) — System V AMD64 ABI investigation, register mapping, pointer and struct passing, and stack argument analysis
- [ch03-MachineLevelRepresentation/miniobjdump](ch03-MachineLevelRepresentation/miniobjdump) — ELF header and section parsing, symbol discovery, and simplified disassembly inspired by objdump
- supporting notes and experiments under the chapter folders

## Why this repo exists

The goal is to build intuition for how programs behave below the high-level source code layer: where locals are stored, how frames are laid out, how arguments move through registers and the stack, how ELF metadata is structured, and how runtime tools infer meaning from machine state.

## Typical workflow

Most exercises are built with:

```bash
gcc -O0 -g -fno-omit-frame-pointer
```

This keeps the stack layout easy to inspect and correlates directly with the concepts discussed in CSAPP. ELF-based tools are also built and exercised against small sample binaries to validate the learning outcomes.

## Repository status

This repository is primarily educational and incremental. It now includes three completed learning projects under the chapter 3 machine-level representation work:

- StackViz for runtime stack analysis
- CallScope for ABI and calling-convention investigation
- MiniObjDump for ELF structural exploration and disassembly basics

The emphasis remains on small, testable programs that make low-level software behavior understandable.
