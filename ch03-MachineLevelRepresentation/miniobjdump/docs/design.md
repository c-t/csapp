## Roadmap

Phase 0 - ELF Investigation     ✅
Phase 1 - ELF Header Viewer     ✅
Phase 2 - Section Viewer        ✅
Phase 3 - Hex Dump             ✅
Phase 4 - Symbol Table Reader  ✅
Phase 5 - Function Discovery   ✅
Phase 6 - Mini Disassembler     ✅
Phase 7 - Section Statistics    ✅
Phase 8 - MiniObjDump v1.0      ✅

# MiniObjDump Design

## Final status

MiniObjDump reached its learning goal: it can parse ELF metadata, resolve section and symbol details, and present function-oriented machine-code views in a simplified objdump-like workflow.

## Goal

Understand ELF internals by implementing a simplified objdump.

---

## Roadmap

### Phase 0 - ELF Investigation ✅

Study:

- file
- readelf
- nm
- objdump

### Phase 1 - ELF Header Viewer ✅

Read:

```c
Elf64_Ehdr
```

Display:

- File type
- Architecture
- Entry point
- Header counts

### Phase 2 - Section Viewer ✅

Read:

```c
Elf64_Shdr
```

Resolve section names through:

```text
.shstrtab
```

### Phase 3 - Hex Dump ✅

Goal

Read actual section contents from the ELF file.

Current Implementation

- Locate `.text`
- Read section bytes
- Display hexadecimal output

Learning Objective

Understand how executable machine code is stored
inside ELF binaries before disassembly.

### Phase 4 - Symbol Table Reader ✅

Goal

Read ELF symbols from:

```text
.symtab
```

and resolve symbol names using:

```text
.strtab
```

Learning Objective

Understand how utilities such as:

```bash
nm
objdump
```

discover function and symbol names.

### Phase 5 - Function Discovery ✅

Goal

Identify executable functions from ELF metadata.

Implementation

Parse:

```c
Elf64_Sym
```

Filter:

```c
ELF64_ST_TYPE(st_info) == STT_FUNC
```

Learning Objective

Understand how disassemblers locate function
entry points before instruction decoding begins.

### Phase 6 - Mini Disassembler ✅

Goal

Associate functions with their machine code.

Implementation

Use:

```text
STT_FUNC
```

symbols from the ELF symbol table.

Map:

```text
Function Address
        ↓
.text Offset
        ↓
Function Bytes
```

Display:

- Function Name
- Address
- Size
- Machine Code Bytes

Learning Objective

Understand how disassemblers connect ELF
metadata to executable code.

### Phase 7 - Section Statistics ✅

Goal

Analyze ELF section sizes.

Implementation

Display:

- Section name
- Section size
- Total section count

Learning Objective

Understand how executable size is distributed
between:

- Code
- Data
- Symbols
- Relocations
- Debug information

### Phase 8 - MiniObjDump v1.0

## Final Architecture

ELF Header
    ↓
Section Header Table
    ↓
Sections

.text
.rodata
.data
.bss

    ↓

.symtab
.strtab

    ↓

Functions

    ↓

Machine Code

    ↓

Function-Aware Disassembly
