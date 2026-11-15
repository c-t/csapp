# MiniObjDump

A simplified implementation of objdump for learning ELF internals.

---

## Project Status

- [x] Phase 0 - ELF Investigation
- [x] Phase 1 - ELF Header Viewer
- [x] Phase 2 - Section Viewer
- [x] Phase 3 - Hex Dump
- [x] Phase 4 - Symbol Table Reader
- [x] Phase 5 - Function Discovery
- [x] Phase 6 - Mini Disassembler
- [x] Phase 7 - Section Statistics
- [x] Phase 8 - MiniObjDump v1.0
---

## Implemented Features

### Phase 1 - ELF Header Viewer

Displays:

- ELF format
- Endianness
- File type
- Entry point
- Program header count
- Section header count

### Phase 2 - Section Viewer

Reads:

```c
Elf64_Shdr
```

and resolves section names using:

```text
.shstrtab
```

Output includes:

```text
.text
.rodata
.data
.bss
.symtab
.strtab
.shstrtab
```

### Phase 3 - Hex Dump

Reads and displays raw bytes from ELF sections.

Current implementation:

```text
.text
```

Example:

```text
00001060: f3 0f 1e fa 31 ed 49 89
00001068: d1 5e 48 89 e2 48 83 e4
```

Verification:

Compared against:

```bash
objdump -d hello
```

The dumped bytes matched the machine code bytes
displayed by objdump.

### Phase 4 - Symbol Table Reader ✅

Reads:

```text
.symtab
.strtab
```

Implementation:

```c
Elf64_Sym
```

Displays:

```text
_start
main
add
printf
```

Verification:

Compared against:

```bash
nm hello
```

The discovered symbol names and addresses matched
the ELF symbol table.

### Phase 5 - Function Discovery ✅

Reads:

```text
.symtab
.strtab
```

Filters:

```text
STT_FUNC
```

to discover executable functions.

Example:

```text
_start
add
main
_init
_fini
```

Key Learning:

Disassemblers do not discover functions by scanning
instructions alone.

ELF symbol tables already provide function metadata.

### Phase 6 - Mini Disassembler ✅

Implementation

Combines:

```text
.symtab
+
.text
```

to display function-specific machine code.

Example:

```text
Function: add
Address : 0x1149
Size    : 24

00001149: f3 0f 1e fa 55 48 89 e5
00001151: 89 7d fc 89 75 f8 8b 55
00001159: fc 8b 45 f8 01 d0 5d c3
```

Key Learning

Function metadata allows raw machine-code bytes
to be associated with specific functions.

### Phase 7 - Section Statistics ✅

Displays size information for all ELF sections.

Example:

```text
.text      311 bytes
.rodata      8 bytes
.data       16 bytes
.bss         8 bytes
.symtab    888 bytes
.strtab    481 bytes
```

Key Learning

ELF binaries contain more than executable code.

Metadata, debugging information, relocation data,
and symbol tables can exceed the size of the
actual machine code.

## Features

MiniObjDump can:

- Parse ELF headers
- Display ELF sections
- Dump `.text` bytes
- Read ELF symbol tables
- Discover executable functions
- Display function-oriented disassembly
- Analyze section statistics

## Verification

This implementation was validated by building the project and running it against ELF samples on x86-64 Linux. The tool successfully reads header metadata, section tables, symbol tables, and function-oriented disassembly output in the same style as `readelf`, `nm`, and `objdump`.
- Generate ELF summary reports

## Learning Outcomes

This project demonstrates:

- ELF file structure
- ELF headers
- Section tables
- String tables
- Symbol tables
- Function metadata
- Machine code storage
- Executable organization
