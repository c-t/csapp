#include <stdio.h>

#include "memviz.h"

int main(int argc, char *argv[])
{
    trace_t trace;

    if (argc != 2)
    {
        printf("Usage: %s <trace-file>\n", argv[0]);
		return 1;
    }

    if (load_trace(argv[1], &trace) < 0)
    {
        return 1;
    }

    print_trace(&trace);
	print_analysis(&trace);

	return 0;
}