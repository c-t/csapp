#include <stdio.h>

static void foo()
{
	int local = 10;
	printf("stack : %p\n", (void*)&local);
}

int main()
{
	foo();
	return 0;
}
