#include <stdio.h>

#define ARR_SIZE 15
#define COUNT	5

void print_arr(int * arr, int len);
void count_sort(int * arr, int * carr);
void print_cSort(int * arr, int len);

int main(void)
{
	int arr[ARR_SIZE] = {1, 3, 2, 4, 3, 2, 5, 3, 1, 2, 3, 4, 4, 3, 5};
	int carr[COUNT] = {0, };

	print_arr(arr, ARR_SIZE);

	count_sort(arr, carr);

	return 0;
}

void print_arr(int * arr, int len)
{
	int i;

	for(i=0; i<len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void count_sort(int *arr, int * carr)
{
	int i;

	for(i=0; i<ARR_SIZE; i++)
	{
		carr[arr[i]-1]++;
	}

	print_cSort(carr, COUNT);
}

void print_cSort(int * carr, int len)
{
	int i, j;

	for(i=0; i<len; i++)
	{
		j = carr[i];
		while(j--)
		{
			printf("%d ", i+1);
		}
	}
	printf("\n");
}
