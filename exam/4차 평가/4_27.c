#include <stdio.h>
#include <stdlib.h>

int add5(int a, int b, int c, int d, int e)
{
	return a+b+c+d+e;
}

int main(void)
{
	int res = 0;

	res = add5(1, 2, 3, 4, 5);
	printf("result = %d\n", res);

	return 0;
}
