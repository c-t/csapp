#include <stdio.h>
#include <stdint.h>

#include "callscope.h"

typedef struct
{
	uint64_t rdi;
	uint64_t rsi;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t r8;
	uint64_t r9;
} argument_registers_t;

#if 0
static void capture_registers(argument_registers_t *regs)
{
	__asm__ volatile("mov %%rdi, %0": "=r"(regs->rdi));
	__asm__ volatile("mov %%rsi, %0": "=r"(regs->rsi));
	__asm__ volatile("mov %%rdx, %0": "=r"(regs->rdx));
	__asm__ volatile("mov %%rcx, %0": "=r"(regs->rcx));
	__asm__ volatile("mov %%r8, %0": "=r"(regs->r8));
	__asm__ volatile("mov %%r9, %0": "=r"(regs->r9));
}

void callscope_dump(void)
{
	argument_registers_t regs;

	capture_registers(&regs);

	printf("\nCallScope Report\n");
	printf("------------------------------\n\n");
	printf("RDI : %lu\n", regs.rdi);
	printf("RSI : %lu\n", regs.rsi);
	printf("RDX : %lu\n", regs.rdx);
	printf("RCX : %lu\n", regs.rcx);
	printf("R8  : %lu\n", regs.r8);
	printf("R9  : %lu\n", regs.r9);
	
	printf("\n");
}

#endif

static void print_abi_visualizer(long a, long b, long c, long d, long e, long f, long g, long h, long i)
{
    printf("\n");

    printf("ABI Visualizer\n");
    printf("==============\n\n");

    printf("Function Call\n");
    printf("--------------------------------\n\n");

    printf("foo(\n");
    printf("    %ld, %ld, %ld,\n", a, b, c);
    printf("    %ld, %ld, %ld,\n", d, e, f);
    printf("    %ld, %ld, %ld\n", g, h, i);
    printf(")\n\n");

    printf("Register File\n");
    printf("--------------------------------\n\n");

    printf("RDI  -> Arg1 -> %ld\n", a);
    printf("RSI  -> Arg2 -> %ld\n", b);
    printf("RDX  -> Arg3 -> %ld\n", c);
    printf("RCX  -> Arg4 -> %ld\n", d);
    printf("R8   -> Arg5 -> %ld\n", e);
    printf("R9   -> Arg6 -> %ld\n", f);

    printf("\n");

    printf("Stack Layout\n");
    printf("--------------------------------\n\n");

    printf("High Address\n\n");

    printf("+----------------------+\n");
    printf("| Arg9 = %-11ld|\n", i);
    printf("+----------------------+\n");

    printf("| Arg8 = %-11ld|\n", h);
    printf("+----------------------+\n");

    printf("| Arg7 = %-11ld|\n", g);
    printf("+----------------------+\n");

    printf("\nLow Address\n\n");

    printf("Summary\n");
    printf("--------------------------------\n\n");

    printf("Register Arguments : 6\n");
    printf("Stack Arguments    : 3\n");
}

void callscope_dump(long a, long b, long c, long d, long e, long f, long g, long h, long i)
{
	printf("\nCallscope Report\n");
	printf("--------------------------------\n\n");
	printf("System V AMD64 ABI\n\n");
	printf("Register Arguments\n");
	printf("--------------------------------\n");
	printf("Arg1 -> RDI : %ld\n", a);
	printf("Arg2 -> RSI : %ld\n", b);
	printf("Arg3 -> RDX : %ld\n", c);
	printf("Arg4 -> RCX : %ld\n", d);
	printf("Arg5 -> R8  : %ld\n", e);
	printf("Arg6 -> R9  : %ld\n", f);
	printf("\n");
	printf("Stack Arguments\n");
	printf("--------------------------------\n");
	printf("Arg7 -> STACK : %ld\n", g);
	printf("Arg8 -> STACK : %ld\n", h);
	printf("Arg9 -> STACK : %ld\n", i);
	
	print_abi_visualizer(a, b, c, d, e, f, g, h, i);
	
	printf("\n");
}