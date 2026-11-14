#include <stdio.h>
#include <stdarg.h>

void sum(int count, ...)
{
    va_list args;

    va_start(args, count);

    int total = 0;

    printf("\n");
    printf("Variadic Function\n");
    printf("-----------------\n");

    for (int i = 0; i < count; i++)
    {
        int value = va_arg(args, int);

        printf("arg[%d] = %d\n", i, value);

        total += value;
    }

    va_end(args);

    printf("\n");
    printf("total = %d\n", total);
}

int main(void)
{
    sum(8, 10, 20, 30, 40, 50, 60, 70, 80);

    return 0;
}
