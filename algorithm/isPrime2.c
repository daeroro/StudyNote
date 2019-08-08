#include <stdio.h>
#include <stdlib.h>

int * arr;

void prime(int num)
{
	int i, j;

	for(i=2; i<=num; i++)
	{
		if(arr[i] != 0)
		{
			for(j=2*i; j<=num; j+=i)
			{
				arr[j] = 0;
			}
		}
	}

	for(i=2; i<=num; i++)
	{
		if(arr[i] != 0)
		{
			printf("%d ", arr[i]);
		}
	}
	printf("\n");
}

int main(void)
{
	int i, num;
	scanf("%d", &num);

	arr = (int *)malloc(sizeof(int) * (num+1));

	for(i=1; i<=num; i++)
		arr[i] = i;

	prime(num);

	return 0;
}
