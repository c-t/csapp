System V AMD64 ABI
Verified via GDB.

Arguments:

arg1 -> RDI arg2 -> RSI arg3 -> RDX arg4 -> RCX arg5 -> R8 arg6 -> R9

Additional arguments:

arg7+ -> Stack

Experiment:

foo(1,2,3,4,5,6,7)

Observed:

RDI = 1 RSI = 2 RDX = 3 RCX = 4 R8 = 5 R9 = 6

Stack: arg7 = 7

Observation: Compiler spills register arguments to stack at -O0.
