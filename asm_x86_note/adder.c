#include <stdio.h>
#include <stdlib.h>

int adder(int a, int b, int c, int d, int e);

int main(void)
{
	int a, b, c, d, e, res = 0;
	a = 1, b = 2, c = 3, d = 4, e = 5;

	res = adder(a, b, c, d, e);
	printf("res = %d\n", res);

	return 0;
}

int adder(int a, int b, int c, int d, int e)
{
	int sum = 0;

	sum = a + b + c + d + e;
	
	return sum;
}
