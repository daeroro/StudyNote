#include <stdio.h>

#define HEAP_SIZE 10

int s_arr[HEAP_SIZE];

void swap(int * arr, int a, int b);
void heapify(int * arr, int h_size, int idx);
void buildMaxHeap(int * arr);
void heap_sort(int * arr);

int main(void)
{
	int i;
	int heap[HEAP_SIZE] = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
	
	printf("original arr----------------\n");
	for(i=0; i<HEAP_SIZE; i++)
		printf("%d ", heap[i]);
	printf("\n");

	buildMaxHeap(heap);
	
	printf("MAX heap--------------------\n");
	for(i=0; i<HEAP_SIZE; i++)
		printf("%d ", heap[i]);
	printf("\n");

	printf("heap sort-------------------\n");
	heap_sort(heap);

	return 0;
}

void swap(int * arr, int a, int b)
{
	int tmp;

	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

void heapify(int * arr, int h_size, int idx)
{
	printf("heapify, %d\n", idx);
	int max, i;	

	if((idx < 0) || ((2*idx + 1) > (h_size -1)))
		return;

	if(2*idx+2 <= h_size-1)
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
/*	
		for(i=0; i<h_size; i++)
			printf("%d ", arr[i]);
		printf("\n");
*/
		heapify(arr, h_size, max);
	}
}

void buildMaxHeap(int *arr)
{
	int i;
	for(i=HEAP_SIZE-1; i>=0; i--)
		heapify(arr, HEAP_SIZE, i);
}

void heap_sort(int *arr)
{
	int i, j, k;
	
	for(i=HEAP_SIZE-1; i>1; i--)
	{
		swap(arr, i, 0);
		
		for(j = i-1; j>=0; j--)
			heapify(arr, i, j);

	for(k=0; k<HEAP_SIZE; k++)
		printf("%d ", arr[k]);
	printf("\n");
	}
/*
	for(i=0; i<HEAP_SIZE; i++)
		printf("%d ", arr[i]);
	printf("\n");
*/
}
