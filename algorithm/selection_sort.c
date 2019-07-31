#include <stdio.h>
#include <stdlib.h>

int idx, m_idx;
void print_arr(int * arr, int len);
void find_min(int * arr, int len);
void swap(int * arr, int idx, int m_idx);
void selection_sort(int * arr, int len);

int main(void)
{
	int arr[10] = {1, 10, 5, 2, 7, 4, 3, 6, 9, 8};
	int len = sizeof(arr)/sizeof(int);
	int i;

	print_arr(arr, len);

	selection_sort(arr, len);	

	print_arr(arr, len);

	return 0;
}

void print_arr(int * arr,  int len)
{
	int i;
	for(i=0; i<len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void find_min(int * arr,  int len)
{
	int i, tmp;
	int min = arr[idx];

	for(i=idx, m_idx = idx; i<len; i++)
	{
		if(min > arr[i])
		{
			min = arr[i];
			m_idx = i;
		}		
	}
	
}

void swap(int * arr, int idx, int m_idx)
{
	int tmp;	

	tmp = arr[idx];
	arr[idx] = arr[m_idx];
	arr[m_idx] = tmp;
}

void selection_sort(int * arr, int len)
{
	int i;
	int tmp;

	for(i = idx; i<len; i++)
	{
		find_min(arr, len);

		swap(arr, idx, m_idx);

		idx++;
	}
}
