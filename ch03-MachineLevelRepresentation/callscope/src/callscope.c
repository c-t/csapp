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
