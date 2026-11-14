# CSAPP Learning Repository

This repository is a hands-on learning workspace for Computer Systems: A Programmer's Perspective (CSAPP). It contains experiments, notes, small programs, and stack-analysis projects focused on understanding how software interacts with hardware, memory, and the operating system at a low level.

## Focus areas

- machine-level representation
- assembly and compiler behavior
- stack frames and calling conventions
- memory layout and pointer arithmetic
- recursion and function-call analysis
- debugging and runtime inspection
- Linux system programming concepts

## Main projects

- [ch03-MachineLevelRepresentation/stackviz](ch03-MachineLevelRepresentation/stackviz) — runtime stack inspection and visualization project
- supporting notes and experiments under the chapter folders

## Why this repo exists

The goal is to build intuition for how programs behave below the high-level source code layer: where locals live, how frames are laid out, how return addresses are tracked, and how debuggers and runtime tools infer meaning from stack memory.

## Typical workflow

Most exercises are built with:

```bash
gcc -O0 -g -fno-omit-frame-pointer
```

This keeps the stack layout easy to inspect and correlates with the concepts discussed in CSAPP.

## Repository status

This project is primarily educational and incremental. It is used to explore stack discipline, debugging, runtime inspection, and system-level behavior through small, testable programs.
