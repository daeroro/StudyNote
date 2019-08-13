#include <stdio.h>

int arr[1001];

int dp(int num)
{
	if(num == 1) return 1;
	if(num == 2) return 3;
	if(arr[num] != 0) return arr[num];

	arr[num] = (dp(num-1) + 2*dp(num-2)) % 10007;

	return arr[num];	
}

int main(void)
{
	int num;

	scanf("%d", &num);
	printf("%d\n", dp(num));

	return 0;
}
