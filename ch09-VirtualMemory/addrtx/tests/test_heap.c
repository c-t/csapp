#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *ptr = malloc(sizeof(int));
	printf("heap : %p\n", (void*)ptr);
	free(ptr);
	return 0;
}
