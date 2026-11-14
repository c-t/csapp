#include "callscope.h"

void foo(long a, long b, long c, long d, long e, long f, long g, long h, long i)
{
	callscope_dump(a, b, c, d, e, f, g, h, i);
}

int main()
{
	foo(1, 2, 3, 4, 5, 6, 7, 8, 9);
	return 0;
}
