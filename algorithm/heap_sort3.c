#include <stdio.h>

#define HEAP_SIZE 10

void print_arr(int *arr, int len);
void swap(int * arr, int a, int b);
void buildMaxHeap(int *arr);
void heapifyDownwards(int *arr, int idx, int heap_size);
void heapSort(int * arr);

int main(void)
{
	int arr[10] = {7, 5, 8, 4, 6, 3, 9, 2, 10, 1};

	print_arr(arr, HEAP_SIZE);

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
		printf("%d ", arr[i]);
	printf("\n");
}

void swap(int *arr, int a, int b)
{
	int tmp;
	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void buildMaxHeap(int * arr)
{
	int i;

	for(i=(HEAP_SIZE-2)/2; i>=0; i--)
		heapifyDownwards(arr, i, HEAP_SIZE);
}

void heapifyDownwards(int *arr, int idx, int heap_size)
{
	int i = idx;
	int max = 2*idx+1;
	do
	{
		if(((max+1) <= (heap_size-1)) && arr[max+1] > arr[max])
		{
			max++;
		}
	
		if(arr[max] > arr[i])
		{
			swap(arr, i, max);
		}

		i = max;
		max = 2*i+1;
		
	}
	while(max <= heap_size-1); 

}

void heapSort(int * arr)
{
	int i, j;
	int heap_size = HEAP_SIZE;

	for(i=(HEAP_SIZE-1); i>0; i--)
	{
		swap(arr, i, 0);
		heap_size--;

		for(j=(heap_size-2)/2; j>=0 && (heap_size !=1); j--)
		{
			heapifyDownwards(arr, j, heap_size);
			print_arr(arr, HEAP_SIZE);
		}
	}
}
