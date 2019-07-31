#include <iostream>
#include <cstdio>

using namespace std;

int num;
int arr[10001];

int main(void)
{
	int i, tmp;

	scanf("%d", &num);

	for(i=0; i<num; i++)
	{
		scanf("%d", &tmp);
		arr[tmp]++;
	}

	for(i=1; i<10001; i++)
	{
		while((arr[i]--) != 0)
		{
			printf("%d\n", i);
		}
	}	

	return 0;
}
