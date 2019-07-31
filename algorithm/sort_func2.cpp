#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

bool comp(int a, int b)
{
	return a > b;
}

int main(void)
{
	int arr[100] = {9, 3, 5, 4, 1, 10, 8, 6, 7, 2};
	int i;

	sort(arr, arr+10, comp);

	for(i=0; i<10; i++)
		printf("%d ", arr[i]);
	printf("\n");
	
	return 0;
}
