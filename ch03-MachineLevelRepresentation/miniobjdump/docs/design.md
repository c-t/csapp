# MiniObjDump Design

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

### Phase 3 - Hex Dump

Read section contents.

### Phase 4 - Symbol Table Reader

Parse:

```text
.symtab
.strtab
```

### Phase 5 - Function Discovery

Identify:

```text
main
add
printf
```

from ELF symbols.

### Phase 6 - Mini Disassembler

Display machine code bytes.

### Phase 7 - Section Statistics

Display section sizes and metadata.

### Phase 8 - MiniObjDump v1.0

Integrate all features.