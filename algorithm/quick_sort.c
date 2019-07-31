#include <stdio.h>

void print_arr(int * arr,  int len);
void swap(int * arr, int a, int b);
void quick_sort(int * arr, int len, int left, int right);

int main(void)
{
	int arr[10] = {1, 10, 5, 8, 7, 6, 4, 3, 2, 9};
	int len = sizeof(arr) / sizeof(int);

	print_arr(arr, len);

	quick_sort(arr, len, 0, len-1);

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

void quick_sort(int * arr, int len, int left, int right)
{
	int pivot = left;
	int i, b_val, s_val, b_idx, s_idx;

	if(left > right)
		return;

	while(1)
	{

		// pivot 값 보다 큰 값의 인덱스를 b_idx에 저장
		for(i=pivot, b_idx = right; i<=right; i++)
		{
			if(arr[pivot] < arr[i])
			{
				b_idx = i;
				break;
			}
		}
		printf("b_idx = %d\n", b_idx);
	
		// pivot 값 보다 작은 값의 인덱스를 s_idx에 저장
		for(i = right, s_idx = pivot; i>=pivot; i--)
		{
			if(arr[pivot] > arr[i])
			{
				s_idx = i;
				break;
			}
		}
		printf("s_idx = %d\n", s_idx);

		//큰 인덱스 < 작은 인덱스 -> 자리바꿈
		if(b_idx < s_idx)
		{
			swap(arr, b_idx, s_idx);
		}
		else //큰 인덱스 > 작은 인덱스 -> 작은 인덱스 - 피벗 자리바꿈
		{
			swap(arr, pivot, s_idx);
			pivot = s_idx;
			break;
		}

	}
	print_arr(arr, len);

	quick_sort(arr, len, left, pivot-1);
	quick_sort(arr, len, pivot +1, right);		
}
