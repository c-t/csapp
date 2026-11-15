# Phase 0 - ELF Investigation

Test Program:

```c
int add(int a, int b)
{
    return a + b;
}
```

Build:

```bash
gcc -g -O0 hello.c -o hello
```

## Findings

### ELF Type

```text
ELF64
Little Endian
PIE Executable
```

### Entry Point

```text
0x1060
```

Associated Symbol:

```text
_start
```

### Important Sections

```text
.text
.rodata
.data
.bss
.symtab
.strtab
```

### Symbol Table

Observed:

```text
add
main
```

via:

```bash
nm hello
```

Conclusion:

Function names are stored in:

```text
.symtab
.strtab
```

### Disassembly

Observed:

```asm
mov $10, %edi
mov $20, %esi
call add
```

This directly matches the System V AMD64 ABI investigated in CallScope.

## Key Learning

ELF binaries contain:

- Metadata
- Sections
- Symbols
- Machine code

Tools such as:

- file
- readelf
- nm
- objdump

are different views over the same ELF structure.

# Phase 1 Results

Input:
./miniobjdump hello

Output:
Format          : ELF64
Endianness      : Little Endian
Type            : DYN
Machine         : x86-64
Entry Point     : 0x1060

Program headers : 14
Section headers : 37

Verification:
Compared against:
readelf -h hello

Result:
All parsed fields matched the ELF header reported by readelf.

# Phase 2 - Section Viewer

Goal

Read the ELF Section Header Table and resolve
human-readable section names.

Implementation

Parsed:

```c
Elf64_Shdr
```

Used:

```text
e_shstrndx
```

to locate:

```text
.shstrtab
```

Section Name Resolution

```text
Section Header
        ↓
Name Offset
        ↓
.shstrtab
        ↓
Actual Section Name
```

Observed Sections

```text
.text
.rodata
.data
.bss
.symtab
.strtab
.shstrtab
```

Key Learning

Section names are not stored directly in
section headers.

Each section header contains an offset into
the section string table.

Verification

Compared output against:

```bash
readelf -S hello
```

Result:

All section names were successfully resolved.
