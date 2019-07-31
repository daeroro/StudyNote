#include <stdio.h>

#define HEAP_SIZE 9

void swap(int * arr, int a, int b);
void heapify(int * arr, int idx);
void buildMaxHeap(int * arr);

int main(void)
{
	int i;
	int heap[HEAP_SIZE] = {7, 6, 5, 8, 3, 5, 9, 1, 6};
	
	for(i=0; i<HEAP_SIZE; i++)
		printf("%d ", heap[i]);
	printf("\n");

	buildMaxHeap(heap);

	for(i=0; i<HEAP_SIZE; i++)
		printf("%d ", heap[i]);
	printf("\n");

	return 0;
}

void swap(int * arr, int a, int b)
{
	int tmp;

	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void heapify(int * arr, int idx)
{
	printf("heapify, %d\n", idx);
	int max, i;	

	if((idx < 0) || ((2*idx + 1) > (HEAP_SIZE -1)))
		return;

	if(2*idx+2 <= HEAP_SIZE-1)
	{//Both children exist.
		if(arr[2*idx+2] > arr[2*idx+1])
			max = 2*idx+2;
		else
			max = 2*idx+1;

		goto swap;
	}
	else
	{//Only left child exists.
		max = 2*idx+1;
	}
	return;

swap:
	if(arr[max] > arr[idx])
	{
		swap(arr, idx, max);
	
		for(i=0; i<HEAP_SIZE; i++)
			printf("%d ", arr[i]);
		printf("\n");

		heapify(arr, max);
	}
}

void buildMaxHeap(int *arr)
{
	int i;
	for(i=HEAP_SIZE-1; i>=0; i--)
		heapify(arr, i);
}
