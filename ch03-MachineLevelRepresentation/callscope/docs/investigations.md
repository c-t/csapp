# Phase 0 Investigation

Test:

```c
foo(1,2,3,4,5,6,7);
```

GDB Evidence:

```text
rdi = 1
rsi = 2
rdx = 3
rcx = 4
r8  = 5
r9  = 6
```

Stack:

```text
0x7fffffffd670: 0x0000000000000007
```

Conclusion:

arg7 is stack passed.