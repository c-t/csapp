# MiniObjDump

A simplified implementation of objdump for learning ELF internals.

---

## Project Status

- [x] Phase 0 - ELF Investigation
- [x] Phase 1 - ELF Header Viewer
- [x] Phase 2 - Section Viewer
- [x] Phase 3 - Hex Dump
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

## Next Phase

### Phase 4 - Symbol Table Reader

Parse:

```text
.symtab
.strtab
```

and display ELF symbols.