#include "callscope.h"

void foo(long a, long b, long c, long d, long e, long f)
{	
	callscope_dump();

	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
}

int main()
{
	foo(1, 2, 3, 4, 5, 6);

	return 0;
}
