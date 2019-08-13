#include <stdio.h>

void swap(int * arr, int a, int b);
void print_arr(int * arr, int len);
void bubble_sort(int * arr, int len);

int main(void)
{
	int arr[3];
	int i;
	
	for(i=0; i<3; i++)
		scanf("%d", &arr[i]);

	bubble_sort(arr, 3);

	print_arr(arr, 3);

	return 0;
}

void swap(int * arr, int a, int b)
{
	int tmp;

	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void print_arr(int * arr, int len)
{
	int i;

	for(i=0; i<len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void bubble_sort(int * arr, int len)
{
	int i, j;

	for(i=0; i<len; i++)
	{
		for(j=i; j>0; j--)
		{
			if(arr[j] < arr[j-1])
			{
				swap(arr, j, j-1);
			}
		}
	}
}
