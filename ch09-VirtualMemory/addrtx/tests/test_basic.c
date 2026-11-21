#include <stdio.h>
#include <stdlib.h>

int global_var = 42;

int main()
{
	int stack_var = 10;
	int *heap_var = malloc(sizeof(int));
	printf("global		: %p\n", (void*)&global_var);
	printf("heap object	: %p\n", (void*)heap_var);
	printf("heap ptr	: %p\n", (void*)&heap_var);
	printf("stack		: %p\n", (void*)&stack_var);
	free(heap_var);
	return 0;
}
