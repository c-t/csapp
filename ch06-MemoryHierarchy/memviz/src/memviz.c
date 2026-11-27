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

	histogram_t page_histogram;
	histogram_t cacheline_histogram;
	build_page_histogram(&trace, &page_histogram);
	build_cacheline_histogram(&trace, &cacheline_histogram);
	print_page_histogram(&page_histogram);
	print_cacheline_histogram(&cacheline_histogram);

	return 0;
}