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

# Phase 3 - Hex Dump

Goal

Read and display raw bytes stored in the `.text`
section.

Implementation

1. Locate `.text` using the Section Header Table.
2. Read section contents using:
   - `sh_offset`
   - `sh_size`
3. Display bytes in hexadecimal form.

Observed

```text
00001060: f3 0f 1e fa 31 ed 49 89
00001068: d1 5e 48 89 e2 48 83 e4
```

Verification

Compared against:

```bash
objdump -d hello
```

Observed:

```asm
1060: f3 0f 1e fa
1064: 31 ed
1066: 49 89 d1
1069: 5e
106a: 48 89 e2
```

The bytes matched exactly.

Key Learning

Executable instructions are stored as raw bytes
inside the `.text` section.

Disassemblers read these bytes and translate them
into human-readable assembly instructions.

ELF Relationship

```text
ELF Header
    ↓
Section Header Table
    ↓
.text
    ↓
Raw Machine Code Bytes
```

# Phase 4 - Symbol Table Reader

Goal

Read symbol information directly from the ELF file.

Implementation

Located:

```text
.symtab
```

Read:

```c
Elf64_Sym
```

Resolved names via:

```text
.strtab
```

Observed

```text
0000000000001149 add
0000000000001161 main
0000000000001060 _start
```

Verification

Compared against:

```bash
nm hello
```

Result

The symbol names and addresses matched
the ELF symbol table.

Key Learning

Symbol names are not stored directly inside
symbol entries.

Each symbol contains an offset into the
ELF string table.

ELF Relationship

```text
.symtab
      ↓
Elf64_Sym
      ↓
st_name
      ↓
.strtab
      ↓
Symbol Name
```
