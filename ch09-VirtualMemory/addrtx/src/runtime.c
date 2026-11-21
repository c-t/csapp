#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "addrtx.h"

static int global_var = 42;

void run_runtime_analysis(void)
{
    int stack_var = 10;

    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL)
    {
        return;
    }

    uint64_t addresses[] =
    {
        (uint64_t)&global_var,
        (uint64_t)heap_var,
        (uint64_t)&heap_var,
        (uint64_t)&stack_var
    };

    size_t count = sizeof(addresses) / sizeof(addresses[0]);

    printf("\nRuntime Address Dataset\n");
    printf("=====================================\n");

    analyze_addresses(addresses, count);

    print_translation_statistics(addresses, count);

    free(heap_var);
}