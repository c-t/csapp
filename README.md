# CSAPP Learning Repository

This repository is a hands-on learning workspace for *Computer Systems: A Programmer's Perspective* (CSAPP). It contains implementation-focused tools, experiments, notes, and small programs that reveal how software interacts with hardware, memory, and the operating system at a low level.

## Featured projects

### Chapter 3: Machine-Level Representation

- [StackViz](ch03-MachineLevelRepresentation/stackviz) — runtime stack and call-frame inspection, recursion tracing, source mapping, and variable lookup
- [CallScope](ch03-MachineLevelRepresentation/callscope) — System V AMD64 ABI behavior, argument mapping, register use, and stack arguments
- [MiniObjDump](ch03-MachineLevelRepresentation/miniobjdump) — ELF parsing, section and symbol inspection, and simplified disassembly

### Chapter 9: Virtual Memory

- [AddrTx](ch09-VirtualMemory/addrtx) — virtual-address decomposition, page classification, page sizes, and process memory regions
- [PTSim](ch09-VirtualMemory/ptsim) — 48-bit address indices and multi-level x86-64 page-table walks
- [TLBSim](ch09-VirtualMemory/tlbsim) — TLB lookup, filling, FIFO/LRU replacement, locality, and hit/miss statistics

## Learning areas

- machine-level representation and assembly
- compiler behavior and calling conventions
- stack frames, pointers, structs, and variadic arguments
- ELF and binary structure
- runtime debugging and symbol resolution
- virtual and physical address translation
- multi-level page tables
- TLB caching and replacement policies
- memory layout and Linux process regions
- low-level operating-system concepts

## Typical workflow

Debuggable C and C++ experiments are generally built with frame-pointer and debug information enabled:

```bash
make
make test
```

Many tools support direct, instrumented sample programs so that stack layouts, register behavior, address translation, and cache effects can be observed without relying only on source-level abstractions.

## Completed learning tracks

- **Machine-level representation:** StackViz, CallScope, and MiniObjDump provide practical views of runtime frames, ABI conventions, ELF metadata, and machine instructions.
- **Virtual memory:** AddrTx, PTSim, and TLBSim form a progression from virtual-address structure through page-table translation and TLB caching.

## Repository status

This repository is educational and incremental. The core Chapter 3 and Chapter 9 projects listed above are implemented as small, testable programs with dedicated documentation, build targets, samples, and tests.

The emphasis remains on making low-level software behavior understandable through working code, observed output, and repeatable experiments.
