#include <stdio.h>
#include "stackviz.h"

void foo(int a, int b)
{
	int x = 10;
	int y = 20;
	stackviz_var_t locals[] = {
		{"x", -88, sizeof(x), "int"},
		{"y", -84, sizeof(y), "int"},
	};

	(void)a;
	(void)b;

	stackviz_dump_vars(__builtin_frame_address(0), locals, sizeof(locals) / sizeof(locals[0]));
	stackviz_dump();

	printf("\na=%d b=%d x=%d y=%d\n", a, b, x, y);
}

int main()
{
	foo(1, 2);
	return 0;
}
