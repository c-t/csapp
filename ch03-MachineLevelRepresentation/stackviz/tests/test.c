#include <stdio.h>

void foo(int a, int b)
{
	int x = 10;
	int y = 20;

	printf("foo\n");
}

int main()
{
	foo(1, 2);
	return 0;
}
