#include <stdio.h>

typedef struct
{
	int x;
	int y;
} point_t;

void foo(int* value, point_t *point)
{
	printf("\nPointer Arguments\n");
	printf("-------------------------------\n");
	printf("value address	: %p\n", (void*)value);
	printf("value content	: %d\n", *value);
	printf("\n");
	printf("point address	: %p\n", (void*)point);
	printf("point->x	: %d\n", point->x);
	printf("point->y	: %d\n", point->y);
}

int main()
{
	int value = 100;

	point_t point = { .x = 10, .y = 20};

	foo(&value, &point);

	return 0;
}
