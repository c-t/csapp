#include <stdio.h>

void foo(long a, long b, long c, long d, long e, long f, long g)
{	
	printf("foo\n");
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	(void)g;
}

int main()
{
	foo(1, 2, 3, 4, 5, 6, 7);
	return 0;
}
