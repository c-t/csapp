# MiniObjDump

A simplified implementation of objdump for learning ELF internals.

---

## Project Status

- [x] Phase 0 - ELF Investigation
- [x] Phase 1 - ELF Header Viewer
- [x] Phase 2 - Section Viewer
- [ ] Phase 3 - Hex Dump
- [ ] Phase 4 - Symbol Table Reader
- [ ] Phase 5 - Function Discovery
- [ ] Phase 6 - Mini Disassembler
- [ ] Phase 7 - Section Statistics
- [ ] Phase 8 - MiniObjDump v1.0

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

---

## Next Phase

Phase 3 - Hex Dump

Display raw bytes from ELF sections.