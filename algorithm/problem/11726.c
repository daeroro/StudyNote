#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr[1001];

int tile(int num);

int main(void)
{
	int num, res;

	scanf("%d", &num);

	arr[1] = 1;
	arr[2] = 2;	

	res = tile(num);
	res %= 10007;
	printf("%d\n", res);
	
	return 0;
}

int tile(int num)
{
	if(num == 1) return 1;
	if(num == 2) return 2;
	if(arr[num] != 0) return arr[num];

	arr[num] = (tile(num-1) + tile(num-2)) % 10007;
	
	return arr[num];
}
