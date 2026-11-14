#define __GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>
#include <stddef.h>
#include <string.h>

#include "stackviz.h"

#define MAX_FRAMES 10

typedef struct
{
	void *rbp;
	void *saved_rbp;
	void *return_address;
	uintptr_t rsp;
	size_t frame_size;
} stack_frame_info_t;

typedef struct
{
	const char *name;
	void *base;
	ptrdiff_t offset;
} symbol_info_t;

static void print_ascii_frame(const stack_frame_info_t *frame);
static void walk_frame_chain(const stack_frame_info_t *frame);

static uintptr_t get_rsp(void)
{
	uintptr_t rsp;
	__asm__ volatile ("mov %%rsp, %0" : "=r"(rsp));
	return rsp;
}

static symbol_info_t resolve_symbol(void *address)
{
	symbol_info_t symbol = 
	{
		.name = "<unknown>",
		.base = NULL,
		.offset = 0
	};

	Dl_info info;

	if(dladdr(address, &info) != 0)
	{
		if(info.dli_sname != NULL)
			symbol.name = info.dli_sname;

		symbol.base = info.dli_saddr;

		if(info.dli_saddr != NULL)
			symbol.offset = (ptrdiff_t)((uintptr_t)address - (uintptr_t)info.dli_saddr);
	}
	return symbol;
}

static void resolve_source_location(void *address, char *buffer, size_t buffer_size)
{
	char command[512];
	char function[128];
	char location[256];
	FILE *fp;
	Dl_info info;
	const char *image_path = "/proc/self/exe";
	uintptr_t candidates[4] = {0, 0, 0, 0};
	size_t candidate_count = 0;

	if(buffer == NULL || buffer_size == 0)
		return;

	buffer[0] = '\0';
	if(address == NULL)
	{
		snprintf(buffer, buffer_size, "<unknown>");
		return;
	}

	if(dladdr(address, &info) != 0)
	{
		if(info.dli_fname != NULL && info.dli_fname[0] != '\0')
			image_path = info.dli_fname;
		if(info.dli_fbase != NULL)
			candidates[candidate_count++] = (uintptr_t)address - (uintptr_t)info.dli_fbase;
		if(info.dli_saddr != NULL)
			candidates[candidate_count++] = (uintptr_t)address - (uintptr_t)info.dli_saddr;
	}

	candidates[candidate_count++] = (uintptr_t)address;
	if(candidate_count > 4)
		candidate_count = 4;

	for(size_t i = 0; i < candidate_count; i++)
	{
		snprintf(command, sizeof(command), "addr2line -f -C -e %s %p 2>/dev/null", image_path, (void *)candidates[i]);
		fp = popen(command, "r");
		if(fp == NULL)
			continue;

		if(fgets(function, sizeof(function), fp) == NULL)
		{
			pclose(fp);
			continue;
		}

		if(fgets(location, sizeof(location), fp) == NULL)
		{
			pclose(fp);
			continue;
		}

		pclose(fp);

		function[strcspn(function, "\r\n")] = '\0';
		location[strcspn(location, "\r\n")] = '\0';

		if(strcmp(location, "??:0") == 0 || strcmp(location, "??") == 0)
			continue;
		if(strcmp(function, "??") == 0 || strcmp(function, "") == 0)
		{
			snprintf(buffer, buffer_size, "%s", location);
			return;
		}
		snprintf(buffer, buffer_size, "%s (%s)", location, function);
		return;
	}

	snprintf(buffer, buffer_size, "<unknown>");
}

static void capture_frame_info(stack_frame_info_t *frame)
{
	frame->rbp = __builtin_frame_address(0); 
	frame->return_address = __builtin_return_address(0);
	frame->saved_rbp = *(void**)frame->rbp;
	frame->rsp = get_rsp();
	frame->frame_size = (uintptr_t)frame->rbp - frame->rsp;
}

static void dump_stack_memory(const stack_frame_info_t *frame, uintptr_t start, uintptr_t end)
{
	for(uintptr_t addr = start; addr < end; addr +=sizeof(uint64_t))
	{
		uint64_t value = *(uint64_t *)addr;
		printf("%p	: 0x%016lx", (void*)addr, value);
		if(addr == (uintptr_t)frame->rbp)
			printf(" <= Saved RBP");
		if(addr == (uintptr_t)frame->rbp + sizeof(void*))
			printf(" <= Return Address");
		printf("\n");
	}
}

static void print_backtrace(const stack_frame_info_t *frame)
{
	void* rbp = frame->rbp;
	printf("\nBacktrace\n");
	printf("-------------------------\n");
	for(int i = 0; i < MAX_FRAMES && rbp != NULL; i++)
	{
		void *saved_rbp = *(void **)rbp;
		void *return_address = *(void **)((char *)rbp + sizeof(void *));
		char source[256];
		
		symbol_info_t symbol = resolve_symbol(return_address);
		resolve_source_location(return_address, source, sizeof(source));
		if(symbol.base != NULL)
			printf("#%-2d %-20s +0x%tx (%p) @ %s\n", i, symbol.name, symbol.offset, return_address, source);
		else
			printf("#%-2d %-20s (%p) @ %s\n", i, symbol.name, return_address, source);

		if(saved_rbp == NULL)
			break;
		
		if(saved_rbp <= rbp)
			break;
		
		rbp = saved_rbp;
	}
}

static void print_recursion_tree(const stack_frame_info_t *frame)
{
	void *rbp = frame->rbp;
	const char *previous_name = NULL;
	int nested_depth = 0;

	printf("\nRecursion Visualization\n");
	printf("----------------------\n");

	for(int i = 0; i < MAX_FRAMES && rbp != NULL; i++)
	{
		void *saved_rbp = *(void **)rbp;
		void *return_address = *(void **)((char *)rbp + sizeof(void *));
		symbol_info_t symbol = resolve_symbol(return_address);
		const char *name = symbol.name;

		if(name == NULL || *name == '\0')
			name = "<unknown>";

		if(previous_name != NULL && strcmp(name, previous_name) == 0)
			nested_depth++;
		else
			nested_depth = 0;

		for(int j = 0; j < nested_depth; j++)
			printf("  ");
		printf("%s\n", name);

		previous_name = name;

		if(saved_rbp == NULL)
			break;
		if(saved_rbp <= rbp)
			break;
		rbp = saved_rbp;
	}
}

static void print_frame_info(const stack_frame_info_t *frame)
{
	printf("\n");
	printf("==========================\n");
	printf("	StackViz Report\n");
	printf("==========================\n");
	printf("RSP			: %p (%#lx)\n", (void*)frame->rsp, (unsigned long)frame->rsp);
	printf("RBP			: %p (%#lx)\n", frame->rbp, (unsigned long)frame->rbp);
	printf("\n");
	printf("Frame Size		: %zu bytes\n", frame->frame_size);	
	printf("\n");
	printf("Saved RBP		: %p\n", frame->saved_rbp);
	printf("Return address		: %p\n", frame->return_address);
	size_t delta = (uintptr_t)frame->saved_rbp - (uintptr_t)frame->rbp;
	printf("Caller Frame Distance	: %zu bytes\n", delta);
	printf("\n");
	printf("==========================\n");
	printf("\n");
	printf("Stack Memory\n");
	dump_stack_memory(frame, frame->rsp, (uintptr_t)frame->rbp + 16);
	printf("RBP+8 value		: %p\n", *(void**)((uintptr_t)frame->rbp+8));
	printf("builtin ret addr	: %p\n", frame->return_address);
	print_ascii_frame(frame);
	print_recursion_tree(frame);
	walk_frame_chain(frame);
	print_backtrace(frame);
}

static void print_ascii_frame(const stack_frame_info_t *frame)
{
	printf("\n");
	printf("Stack Frame Layout\n\n");
	printf("High Address\n");
	printf("	|\n");
	printf("	V\n\n");
	printf("+-------------------------------+\n");
	printf("| Return Address		|\n");
	printf("| %p |\n", (void*)((uintptr_t *)frame->rbp)[1]);
	printf("+-------------------------------+\n");
	printf("| Saved RBP			|\n");
	printf("| %p |\n",frame->saved_rbp);
	printf("+-------------------------------+\n");
       	printf("| Frame Area			|\n");
	printf("| %zu bytes |\n", frame->frame_size);
	printf("+-------------------------------+\n");
	printf("	^\n");
	printf("	|\n");
	printf("Low Address\n");	
}

static void walk_frame_chain(const stack_frame_info_t *frame)
{
	void *rbp = frame->rbp;
	printf("\nFrame Chain\n");
	printf("===========================\n\n");
	for(int i = 0; i < MAX_FRAMES && rbp != NULL; i++)
	{
		void *saved_rbp;
		void *return_address;
		size_t frame_size = 0;

		saved_rbp = *(void**)rbp;
		return_address = *(void**)((char*)rbp + sizeof(void*));
		
		printf("Frame #%d\n", i);
		printf("RBP 		: %p\n", rbp);
		printf("Saved RBP	: %p\n", saved_rbp);
		printf("Return address	: %p\n", return_address);
		
		if(saved_rbp != NULL && saved_rbp > rbp)
			frame_size = (uintptr_t)saved_rbp - (uintptr_t)rbp;

		printf("Frame size	: %zu\n", frame_size);
		printf("\n");

		if(saved_rbp <= rbp)
			break;
		
		rbp = saved_rbp;
	}
}

void stackviz_dump_vars(void *frame_base, const stackviz_var_t *vars, size_t count)
{
	void *rbp = frame_base;
	printf("\nLocal Variable Discovery\n");
	printf("------------------------\n");

	for(size_t i = 0; i < count; i++)
	{
		const stackviz_var_t *var = &vars[i];
		void *addr = (char *)rbp + var->offset;
		uint64_t raw = 0;

		if(var->size == sizeof(int))
			raw = (uint64_t)*(int *)addr;
		else if(var->size == sizeof(long))
			raw = (uint64_t)*(long *)addr;
		else if(var->size == sizeof(long long))
			raw = (uint64_t)*(long long *)addr;
		else if(var->size == sizeof(void *))
			raw = (uint64_t)(uintptr_t)*(void **)addr;
		else
			raw = *(uint64_t *)addr;

		printf("%s\t: %s = %llu (%p) @ %p\n",
			var->name,
			var->type_name,
			(unsigned long long)raw,
			addr,
			addr);
	}
}

void stackviz_dump(void)
{
	stack_frame_info_t frame;
	capture_frame_info(&frame);
	print_frame_info(&frame);
}
