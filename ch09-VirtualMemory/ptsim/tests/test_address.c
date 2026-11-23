#include <stdio.h>

int global_var = 42;

int main()
{
	int stack_var = 10;
	printf("global	: %p\n", (void*)&global_var);
	printf("stack	: %p\n", (void*)&stack_var);
	return 0;
}
