#include <stdio.h>

typedef struct
{
    long a;
    long b;
    long c;
    long d;
    long e;
} big_t;

void foo(big_t value)
{
    printf("\n");
    printf("Large Struct Argument\n");
    printf("---------------------\n");

    printf("a = %ld\n", value.a);
    printf("b = %ld\n", value.b);
    printf("c = %ld\n", value.c);
    printf("d = %ld\n", value.d);
    printf("e = %ld\n", value.e);
}

int main(void)
{
    big_t value =
    {
        .a = 10,
        .b = 20,
        .c = 30,
        .d = 40,
        .e = 50
    };

    foo(value);

    return 0;
}