#include <stdio.h>

long long arr[1000001][2];

long long dp(long long num)
{
	int i;
	for(i=3; i<=num; i++)
	{
		arr[i][1] = (arr[i-1][1] + arr[i-3][0]) % 1000000007;
		arr[i][0] = (2 * arr[i-1][0] + 3 * arr[i-2][0] + 2 * arr[i][1]) % 1000000007;
	}

	return arr[num][0];
}

int main(void)
{
	long long num;

	arr[1][0] = 2;
//	arr[1][1] = 0;
	arr[2][0] = 7;
	arr[2][1] = 1;
//	arr[3][0] = 22;
//	arr[3][1] = 0;

	scanf("%lld", &num);
	printf("%lld\n", dp(num));

	return 0;
}
