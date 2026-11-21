#include <stdio.h>

int global_var = 42;

int main()
{
	printf("global : %p\n", (void*)&global_var);
	return 0;
}
