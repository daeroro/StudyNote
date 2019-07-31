#include <stdio.h>

void print_arr(int * arr, int len);
void swap(int * arr,  int a, int b);
void insertion_sort(int * arr, int len);

int main(void)
{
	int arr[10] = {1, 10, 5, 8, 7, 6, 4, 3, 2, 9};
	int len = sizeof(arr) / sizeof(int);

	print_arr(arr, len);

	insertion_sort(arr, len);

	print_arr(arr, len);

	return 0;
}

void print_arr(int * arr, int len)
{
	int i;

	for(i=0; i<len; i++)
		printf("%d ", arr[i]);

	printf("\n");
}

void swap(int * arr, int a, int b)
{
	int tmp;
	
	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void insertion_sort(int * arr, int len)
{
	int i, j, idx;

	for(i=0; i<len; i++)
	{
		idx = i;

		for(j=idx; j>0; j--)
		{
			if(arr[idx] < arr[j-1])
			{
				swap(arr, j, j-1);
				idx = j-1;
			}
		}
	}
}
