#include <stdio.h>

typedef struct
{
    long x;
    long y;
} point_t;

void foo(point_t point)
{
    printf("\n");
    printf("Small Struct Argument\n");
    printf("---------------------\n");

    printf("point.x : %ld\n", point.x);
    printf("point.y : %ld\n", point.y);
}

int main(void)
{
    point_t point =
    {
        .x = 10,
        .y = 20
    };

    foo(point);

    return 0;
}
