#include <stdio.h>
#include <stdbool.h>

#define NODE 	8
#define TRUE 	1
#define FALSE 	0

void unionParent(int * arr, int a, int b);
int getParent(int * arr, int min);
bool findUnion(int * arr, int a, int b);

int main(void)
{
	int arr[11];
	int i;

	for(i=1; i<=10; i++)
	{
		arr[i] = i;
	}

	unionParent(arr, 1, 2);
	unionParent(arr, 2, 3);
	unionParent(arr, 3, 4);
	unionParent(arr, 5, 6);
	unionParent(arr, 6, 7);
	unionParent(arr, 7, 8);

/*
	for(i=1; i<=10; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
*/
	printf("1-5 ? %d\n", findUnion(arr, 1, 5));

	unionParent(arr, 1, 5);

	printf("1-5 ? %d\n", findUnion(arr, 1, 5));

	return 0;
}

void unionParent(int * arr, int a, int b)
{
	int i;
	int min = (arr[a] <= arr[b]) ? arr[a] : arr[b];
	int max = (arr[a] <= arr[b]) ? arr[b] : arr[a];	

	if(!findUnion(arr, a, b))
	{
		for(i=1; i<=NODE; i++)
		{
			if(arr[i] == max)
			{
				arr[i] = min;
			}
		}
	}
	
	for(i=1; i<=10; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int getParent(int * arr, int min)
{
	int p = min;

	while(p != arr[p])
	{
		p = arr[p];
	}

	return p;
}

bool findUnion(int * arr, int a, int b)
{
	if(arr[a] == arr[b])
		return TRUE;
	else
		return FALSE;
}
