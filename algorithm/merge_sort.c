#include <stdio.h>

#define NUM	8

int s_arr[NUM];
int s_idx;

void print_arr(int * arr, int len);
void swap(int * arr, int a, int b);
void merge_sort(int * arr, int a, int b);
void merge(int * arr, int * s_arr, int a, int middle, int b);

int main(void)
{
	int arr[NUM] = {7, 6, 5, 8, 3, 4, 9, 1};
	int len = sizeof(arr)/sizeof(int);

	print_arr(arr, len);

	merge_sort(arr, 0, len-1);

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

void merge_sort(int * arr, int a, int b)
{
	int middle;

	middle = (a + b) / 2;
	//printf("a = %d, middle = %d, b = %d\n", a, middle, b);

	if(a == middle)
		goto merge;

	merge_sort(arr, a, middle);
	merge_sort(arr, middle+1, b);

merge:

	merge(arr, s_arr, a, middle, b);
}

void merge(int * arr, int * s_arr, int a, int middle, int b)
{
	printf("merge function, a = %d, b = %d\n", a, b);
	int i, j, k, l;
	
	i = a;
	j = middle + 1;
	k = a;

	while((i <= middle) && (j <= b))
	{
		if(arr[i] < arr[j])
		{
			s_arr[k++] = arr[i++];
		}
		else
		{
			s_arr[k++] = arr[j++];
		}
	}

	while(i <= middle)
	{
		s_arr[k++] = arr[i++];
	}

	while(j <= b)
	{
		s_arr[k++] = arr[j++];
	}

	for(i=0, j=a; i<(b-a+1); i++, j++)
	{
		arr[j] = s_arr[j];
	}

	print_arr(arr, NUM);

}
