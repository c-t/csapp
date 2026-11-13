#include "stackviz.h"

int factorial(int n)
{
	if(n ==1)
	{
		stackviz_dump();
		return 1;
	}
	
	return n*factorial(n-1);
}

int main()
{
	factorial(5);
	return 0;
}
