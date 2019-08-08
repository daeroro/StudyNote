#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int num)
{
	int i;
	for(i=2; i<num; i++)
	{
		if(num % i == 0)
			return false;
	}

	return true;
}

bool isPrime2(int num)
{
	int i, end = (int)sqrt(num);
	for(i=2; i<=end; i++)
	{
		if(num % i == 0)
			return false;
	}
	return true;
}

int main(void)
{
	int num;
	scanf("%d", &num);

	printf("%d is prime number? %d\n", num, isPrime(num));
	printf("%d is prime number? %d\n", num, isPrime2(num));

	return 0;
}
