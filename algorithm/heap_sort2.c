#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 10

void print_arr(int * arr, int len);
void swap(int *arr, int a, int b);
void buildMaxHeap(int * arr);
void heapify(int * arr, int idx, int heap_size);
void heapSort(int * arr);

int main(void)
{
	int arr[HEAP_SIZE] = {7, 5, 8, 4, 6, 3, 9, 2, 10, 1};

	print_arr(arr, 10);

	buildMaxHeap(arr);

	print_arr(arr, HEAP_SIZE);

	heapSort(arr);

	print_arr(arr, HEAP_SIZE);

	return 0;
}

void print_arr(int * arr, int len)
{
	int i;

	for(i=0; i<len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int *arr, int a, int b)
{
	int tmp;

	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void buildMaxHeap(int *arr)
{
	int i;

	for(i = (HEAP_SIZE-2)/2; i>=0; i--)
	{
		heapify(arr, i, HEAP_SIZE);
	}
}

void heapify(int * arr, int idx, int heap_size)
{
	int max;
	int i = idx;
	
	do{
		max = 2*i+1;

		if(((max+1) <= (heap_size-1)) && (arr[max+1] > arr[max]))
		{
				max++;
		}

		if(arr[max] > arr[i])
		{
			swap(arr, i, max);
		}
		
		i = (i-1)/2;
	}
	while(i > 0);
}

void heapSort(int * arr)
{
	int i, idx, heap_size;
	heap_size = HEAP_SIZE;
	
	for(idx = HEAP_SIZE-1; idx>0; idx--)
	{
		printf("%d\n", heap_size);
		print_arr(arr, HEAP_SIZE);
		swap(arr, idx, 0);
		heap_size--;

		for(i=idx-1; i>=0; i--)
		{
			if((i<=(heap_size-2)/2) && (heap_size != 1))
			{
				heapify(arr, i, heap_size);
			}
		}
		print_arr(arr, HEAP_SIZE);
	}
}
