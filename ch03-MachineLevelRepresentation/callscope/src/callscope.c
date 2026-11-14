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
} register_snapshot_t;

static void capture_register_snapshot(register_snapshot_t *regs)
{
	__asm__ volatile("mov %%rdi, %0": "=r"(regs->rdi));
	__asm__ volatile("mov %%rsi, %0": "=r"(regs->rsi));
	__asm__ volatile("mov %%rdx, %0": "=r"(regs->rdx));
	__asm__ volatile("mov %%rcx, %0": "=r"(regs->rcx));
	__asm__ volatile("mov %%r8,  %0": "=r"(regs->r8));
	__asm__ volatile("mov %%r9,  %0": "=r"(regs->r9));
}

static void print_register_inspector(const register_snapshot_t *regs)
{
	printf("\nRegister Inspector\n");
	printf("------------------------------\n\n");
	printf("RDI : %lu\n", regs->rdi);
	printf("RSI : %lu\n", regs->rsi);
	printf("RDX : %lu\n", regs->rdx);
	printf("RCX : %lu\n", regs->rcx);
	printf("R8  : %lu\n", regs->r8);
	printf("R9  : %lu\n", regs->r9);
	
	printf("\n");
}

void callscope_dump(long a, long b, long c, long d, long e, long f, long g, long h, long i)
{
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	(void)g;
	(void)h;
	(void)i;
	register_snapshot_t snapshot;
	capture_register_snapshot(&snapshot);
	print_register_inspector(&snapshot);

	printf("\n");
}
