#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int main(void)
{
	int arr[100] = {9, 3, 5, 4, 1, 10, 8, 6, 7, 2};
	int i;

	sort(arr, arr+10);

	for(i=0; i<10; i++)
		printf("%d ", arr[i]);
	printf("\n");
	
	return 0;
}
