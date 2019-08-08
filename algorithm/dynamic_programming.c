#include <stdio.h>

#define NUM	50

int arr[NUM+1] = {1, 1};

int fibo_recur(int num);
int fibo(int num);

int main(void)
{
	int res;

	res = fibo_recur(10);

	printf("recursive res = %d\n", res);	

	res = fibo(10);
	printf("non recursive res = %d\n", res);

	return 0;
}

int fibo_recur(int num)
{
	if(num == 1) return 1;
	if(num == 2) return 1;

	return fibo_recur(num-1) + fibo_recur(num-2);	
}

int fibo(int num)
{
	if(num == 1) return 1;
	if(num == 2) return 1;
	if(arr[num] != 0) return arr[num];

	arr[num] = fibo(num-1) + fibo(num-2);

	return arr[num];
}
